#include "Boss.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "BossProjectile.h"
#include "BossEye.h"
#include "Map3.h"
#include "Player.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "BossPart.h"
#include "BossUpgradedWeapon.h"


#include <math.h>
#include <fstream>


Boss::Boss(int difficulty) {
	this->difficulty = difficulty;
	setType("Boss");
	setSprite("Boss");
	setPosition(df::Vector(10, 10));
	moveCountdown = 30;
	registerInterest(df::STEP_EVENT);
	setSolidness(df::SOFT);
	fireCountdown = fireSlowdown;
	switch (difficulty) {
		case 0:
			maxHP = 4;
			fireSlowdown = 100;
			fireSlowdown2 = 150;
			invincibleCD = 1000;
			break;
		case 1:
			maxHP = 6;
			fireSlowdown = 80;
			fireSlowdown2 = 120;
			invincibleCD = 150;

			break;
		case 2:
			maxHP = 8;
			fireSlowdown = 60;
			fireSlowdown2 = 90;
			invincibleCD = 200;
			break;
		default:
			maxHP = 4;
			fireSlowdown = 100;
			fireSlowdown2 = 150;
			invincibleCD = 100;
			break;
	}
	fireCountdown = fireSlowdown;
	fireCountdown2 = fireSlowdown2;
	hp = maxHP;
	setStage(1);
}

void Boss::defeat() {
	auto ol = WM.objectsOfType("Map3");
	if (!ol.isEmpty()) {
		auto oli = df::ObjectListIterator(&ol);
		auto *p_map3 = dynamic_cast<Map3 *>(oli.currentObject());
		difficulty = p_map3->getDifficulty();
		p_map3->stop(0); // boss died
	}

	FILE *pFile;
	auto ol2 = df::ObjectList(WM.objectsOfType("Player"));
	auto oli2 = df::ObjectListIterator(&ol2);
	auto *p_player = dynamic_cast<Player *>(oli2.currentObject());
	int longestTime = p_player->getClock()->delta() / 100000;

	int scoreList[4];


	std::fstream myFile;
	switch (difficulty) {
		case 0:
			myFile.open("../game/easyScoreBoard.txt", std::ios::in);
			break;
		case 1:
			myFile.open("../game/normalScoreBoard.txt", std::ios::in);
			break;
		case 2:
			myFile.open("../game/difficultScoreBoard.txt", std::ios::in);
			break;
	}
	if (myFile.is_open()) {
		std::string line;
		int lineCount = 0;
		while (getline(myFile, line)) {
			int l = std::stoi(line);

			if (l <= longestTime) {
				scoreList[lineCount] = l;
			} else {
				scoreList[lineCount] = longestTime;
				longestTime = l;
			}
			lineCount++;
		}
		myFile.close();
	} else {
		LM.writeLog("Error: Easy scoreboard not found r");
	}

	switch (difficulty) {
		case 0:
			myFile.open("../game/easyScoreBoard.txt", std::ios::out);
			break;
		case 1:
			myFile.open("../game/normalScoreBoard.txt", std::ios::out);
			break;
		case 2:
			myFile.open("../game/difficultScoreBoard.txt", std::ios::out);
			break;
	}

	if (myFile.is_open()) {
		for (int i = 0; i <= 2; i++) {
			int a = scoreList[i];
			myFile << a << std::endl;
		}
		myFile.close();
	} else {
		LM.writeLog("Error: scoreboard not found");
	}
	WM.markForDelete(this);
}

int Boss::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		bool withinX = (getPosition().getX() < DM.getHorizontal() - 3) && (getPosition().getX() > 3);
		bool withinY = (getPosition().getY() < DM.getVertical() - 10) && (getPosition().getY() > 2);
		bool outOfCage = (getPosition().getX() < 64) || (getPosition().getY() > 11);
		if (moveCountdown > 0 && withinX
		    && withinY && outOfCage) {
			moveCountdown--;
		} else {
			int x = rand() % (DM.getHorizontal() - 10) + 5;
			int y = rand() % (DM.getVertical() - 15) + 5;
			df::Vector direction(x, y);
			direction = (direction - getPosition());
			direction.normalize();
			direction.scale(0.5);
			direction = df::Vector(direction.getX(), direction.getY() / 2);
			setVelocity(direction);
			moveCountdown = 30;
		}

		if (fireCountdown <= 0) {
			fire();
			fireCountdown = fireSlowdown;
		} else {
			fireCountdown--;
		}
		if (stage == 2) {
			if (fireCountdown2 <= 0) {
				fire2();
				fireCountdown2 = fireSlowdown2;
			} else {
				fireCountdown2--;
			}
			if (invincibleCD > 0) {
				DM.drawString(df::Vector(73, 23), "Boss Becomes Invincible", df::RIGHT_JUSTIFIED, df::WHITE);
				DM.drawString(df::Vector(73, 24), "Shoot Down Boss Crystals with Bow", df::RIGHT_JUSTIFIED, df::WHITE);
				sf::CircleShape shape(80);
				shape.setFillColor(sf::Color(237, 247, 84, 100));
				shape.setPosition(df::spacesToPixels(getPosition()).getX() - 75,
				                  df::spacesToPixels(getPosition()).getY() - 50);
				DM.getWindow()->draw(shape);
				invincible = true;
				invincibleCD--;
			} else {
				invincible = false;
			}
		}
		return 1;
	}

	return 0;
}

int Boss::getHp() const {
	return hp;
}

void Boss::setHp(int Hp) {
	hp = Hp;
	if (hp <= 0)
		defeat();

	if (hp == maxHP / 2) {
		setStage(2);
		new BossEye(this);
		df::addParticles(df::RAIN, df::LEFT, 4.0, df::MAGENTA);
	}
}

void Boss::fire() {
	RM.getSound("Charge")->play();
	for (int i = 0; i <= 6; i++) {
		auto b = new BossProjectile(getPosition());
		df::Vector a(tan(1 + i * 17.5), 1);
		a.normalize();
		b->setDirection(a);
		b->setVelocity(df::Vector(b->getVelocity().getX(), b->getVelocity().getY() / 2));
	}
}

void Boss::fire2() {
	auto b = new BossUpgradedWeapon(getPosition(), difficulty);
	int x = rand() % (DM.getHorizontal() - 20) + 10;
	df::Vector position(x, 40);
	df::Vector direction = position - getPosition();
	direction.normalize();
	b->setDirection(direction);
	b->setVelocity(df::Vector(b->getVelocity().getX(), b->getVelocity().getY() / 2));
}

void Boss::setStage(int stage) {
	Boss::stage = stage;
}

bool Boss::getInvincible() const {
	return invincible;
}
