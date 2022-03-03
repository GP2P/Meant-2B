
#include "BossCrystal.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "Boss.h"
#include "Player.h"
#include "LogManager.h"
#include "ResourceManager.h"

BossCrystal::BossCrystal(df::Vector boss_pos, int difficulty) {
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
	// Set other object properties.
	setType("BossCrystal");
	setSprite("BossCrystal");

	// Set starting location, based on boss's position passed in.
	df::Vector p(boss_pos.getX(), boss_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(0.4);

	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);

	stage = 1;
	switch (difficulty) {
		case 0:
			movecd = 130;
			break;
		case 1:
			movecd = 90;
			break;
		case 2:
			movecd = 65;
			break;
		default:
			movecd = 130;
			break;
	}
}

int BossCrystal::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if (p_ce->getObject1()->getType() == "Player") {
			dynamic_cast<Player *> (p_ce->getObject1())->defeat();
			WM.markForDelete(this);
			return 1;
		} else if (p_ce->getObject2()->getType() == "Player") {
			dynamic_cast<Player *> (p_ce->getObject2())->defeat();
			WM.markForDelete(this);
			return 1;
		}
		if ((p_ce->getObject1()->getType() == "Cage") ||
		    (p_ce->getObject2()->getType() == "Cage")) {
			WM.markForDelete(this);
			return 1;
		}
		if ((p_ce->getObject1()->getType() == "Block") ||
		    (p_ce->getObject2()->getType() == "Block")) {
			WM.markForDelete(this);
			return 1;
		}
		if ((p_ce->getObject1()->getType() == "Arrow") ||
		    (p_ce->getObject2()->getType() == "Arrow")) {
			auto crystal = RM.getSound("Crystal");
			crystal->play();
			WM.markForDelete(p_ce->getObject1());
			WM.markForDelete(p_ce->getObject2());
			return 1;
		}
	}
	if (p_e->getType() == df::STEP_EVENT) {
		if (getPosition().getY() >= 20 && stage == 1) {
			setSpeed(0);
			stage = 2;
		}
		if (stage == 2) {
			if (movecd > 0) {
				movecd--;
			} else if (movecd == 0) {
				df::Vector position(40, 0);
				auto ol = df::ObjectList(WM.objectsOfType("Player"));
				auto oli = df::ObjectListIterator(&ol);
				while (!oli.isDone()) {
					auto *p_player = dynamic_cast<Player *>(oli.currentObject());
					if (p_player->isMap3OnGround()) {
						position = p_player->getPosition();
						break;
					}
					oli.next();
				}
				df::Vector direction = position - getPosition();
				direction.setY(direction.getY() * 2);
				direction.normalize();
				setDirection(direction);

				setSpeed(1);
				setVelocity(df::Vector(getVelocity().getX(), getVelocity().getY() / 2));
				movecd = -1;
			}
		}
		return 1;
	}
	return 0;
}

