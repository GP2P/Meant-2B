#include "Arrow.h"
#include "EventStep.h"

Arrow::Arrow(df::Vector player_pos) {

	// Link to "bullet" sprite.
	setSprite("Arrow");

	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
	// Set other object properties.
	setType("Arrow");

	// Set starting location, based on hero's position passed in.
	df::Vector p(player_pos.getX() + 3, player_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);
}

int Arrow::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		setVelocity(getVelocity() + df::Vector(0, 1));
		return 1;
	}

	return 0;
}