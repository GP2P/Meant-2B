#include "Boss.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "BossProjectile.h"
#include "Boss2.h"
#include "BossEye.h"
#include "Map3.h"
#include "LogManager.h"
#include "Player.h"

#include <math.h>
#include <fstream>


Boss::Boss() {
	setType("Boss");
	setSprite("Boss");
	setPosition(df::Vector(10, 10));
	moveCountdown = 30;
	registerInterest(df::STEP_EVENT);
	setSolidness(df::SOFT);
	hp = 5;
	fireSlowdown = 60;
	fireCountdown = fireSlowdown;
	hp = 5;
	new Boss2(this);
	new BossEye(this);

}


int Boss::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		if (hp <= 0) {
            int difficulty = -1;
            auto ol = WM.objectsOfType("Map3");
            if (!ol.isEmpty()) {
                auto oli = df::ObjectListIterator(&ol);
                auto *p_map3 = dynamic_cast<Map3 *>(oli.currentObject());
                difficulty = p_map3->getDifficulty();
                p_map3->stop();
            }

            FILE* pFile;
            auto ol2 = df::ObjectList(WM.objectsOfType("Player"));
            auto oli2 = df::ObjectListIterator(&ol2);
            auto *p_player = dynamic_cast<Player *>(oli2.currentObject());
            int longestTime = p_player->getClock()->delta()/100000;

            int scoreList[4];


            std::fstream myFile;
            switch(difficulty){
                case 0:
                    myFile.open("../game/easyScoreBoard.txt", std::ios::in);
                    break;
                case 1:
                    myFile.open("../game/normalScoreBoard.txt", std::ios::in);
                    break;
                case 2:
                    myFile.open("../game/hardScoreBoard.txt", std::ios::in);
                    break;
            }
            if (myFile.is_open()) {
                std::string line;
                int lineCount = 0;
                while(getline(myFile,line)){
                    int l = std::stoi(line);

                    if( l<=longestTime){
                        scoreList[lineCount] = l;
                    } else{
                        scoreList[lineCount] = longestTime;
                        longestTime = l;
                    }
                    lineCount++;
                }
                myFile.close();
            } else{
                LM.writeLog("Error: Easy scoreboard not found r");
            }

            switch(difficulty){
                case 0:
                    myFile.open("../game/easyScoreBoard.txt", std::ios::out);
                    break;
                case 1:
                    myFile.open("../game/normalScoreBoard.txt", std::ios::out);
                    break;
                case 2:
                    myFile.open("../game/hardScoreBoard.txt", std::ios::out);
                    break;
            }
            if (myFile.is_open()) {
                for(int i=0; i<=2; i++){
                    int a = scoreList[i];
                    myFile<<a<<std::endl;
                }
                myFile.close();
            } else{
                LM.writeLog("Error: Easy scoreboard not found w");
            }
            WM.markForDelete(this);
            return 1;
        }

		bool withinX = (getPosition().getX() < DM.getHorizontal() - 3) && (getPosition().getX() > 3);
		bool withinY = (getPosition().getY() < DM.getVertical() - 7) && (getPosition().getY() > 2);
		bool outOfCage = (getPosition().getX() < 64) || (getPosition().getY() > 11);
		if (moveCountdown > 0 && withinX
		    && withinY && outOfCage) {
			moveCountdown--;
		} else {
			int x = rand() % (DM.getHorizontal() - 10) + 5;
			int y = rand() % (DM.getVertical() - 10) + 5;
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
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if ((p_ce->getObject1()->getType() == "Player") ||
		    (p_ce->getObject2()->getType() == "Player")) {
			WM.markForDelete(p_ce->getObject1());
			WM.markForDelete(p_ce->getObject2());
			return 1;
		}
	}
	return 0;
}

int Boss::getHp() const {
	return hp;
}

void Boss::setHp(int Hp) {
	hp = Hp;
}

void Boss::fire() {
	for (int i = 0; i <= 6; i++) {
		auto b = new BossProjectile(getPosition());
		df::Vector a(tan(1 + i * 17.5), 1);
		a.normalize();
		b->setDirection(a);
		b->setVelocity(df::Vector(b->getVelocity().getX(), b->getVelocity().getY() / 2));
	}
}
