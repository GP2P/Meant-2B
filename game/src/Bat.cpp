#include "Bat.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "Player.h"

Bat::Bat() {
	setType("Bat");
	setSprite("Bat");
	setPosition(df::Vector(rand() % (DM.getHorizontal() - 10) + 5, rand() % (DM.getVertical() - 10) + 5));
	moveCountdown = 30;
	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
	setSolidness(df::SOFT);
}

int Bat::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		if (moveCountdown > 0 && (getPosition().getX() < DM.getHorizontal() - 2) && (getPosition().getX() > 2)
		    && (getPosition().getY() < DM.getVertical() - 7) && (getPosition().getY() > 1)) {
			moveCountdown--;
		} else {
			auto direction = df::Vector(rand() % (DM.getHorizontal() - 10) + 5, rand() % (DM.getVertical() - 10) + 5) -
			                 getPosition();
			direction.normalize();
			direction.scale(0.5);
			direction = df::Vector(direction.getX(), direction.getY() / 2);
			setVelocity(direction);
			moveCountdown = 30;
		}
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if (p_ce->getObject1()->getType() == "Player") {
			dynamic_cast<Player *> (p_ce->getObject1())->defeat();
			WM.markForDelete(this);
		} else if (p_ce->getObject2()->getType() == "Player") {
			dynamic_cast<Player *> (p_ce->getObject2())->defeat();
			WM.markForDelete(this);
		}
	}
	return 0;
}
