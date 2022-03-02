#include "BossProjectile.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "Boss.h"
#include "Player.h"

BossProjectile::BossProjectile(df::Vector boss_pos) {
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
	// Set other object properties.
	setType("BossProjectile");
	setSprite("BossProjectile");

	// Set starting location, based on boss's position passed in.
	df::Vector p(boss_pos.getX(), boss_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(0.4);

	registerInterest(df::COLLISION_EVENT);
}

int BossProjectile::eventHandler(const df::Event *p_e) {
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
	}
	return 0;
}
