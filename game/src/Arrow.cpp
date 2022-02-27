#include "Arrow.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "Boss.h"

Arrow::Arrow(df::Vector player_pos) {

	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
	// Set other object properties.
	setType("Arrow");

	setSprite("ArrowLeft");
	// Set starting location, based on hero's position passed in.
	df::Vector p(player_pos.getX(), player_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);

	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
}

int Arrow::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		setVelocity(getVelocity() + df::Vector(0, 0.004));
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if (p_ce->getObject1()->getType() == "Boss") {
			WM.markForDelete(this);
			Boss *p_b = dynamic_cast <Boss *> (p_ce->getObject1());
			p_b->setHp(p_b->getHp() - 1);
			return 1;
		}
		if (p_ce->getObject2()->getType() == "Boss") {
			WM.markForDelete(this);
			Boss *p_b = dynamic_cast <Boss *> (p_ce->getObject2());
			p_b->setHp(p_b->getHp() - 1);
			return 1;
		}
		if ((p_ce->getObject1()->getType() == "Bat") ||
		    (p_ce->getObject2()->getType() == "Bat")) {
			WM.markForDelete(p_ce->getObject1());
			WM.markForDelete(p_ce->getObject2());
			return 1;
		}
		if ((p_ce->getObject1()->getType() == "Block") ||
		    (p_ce->getObject2()->getType() == "Block")) {
			setVelocity(df::Vector(0, 0));
			return 1;
		}
	}
	return 0;
}