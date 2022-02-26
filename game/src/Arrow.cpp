#include "Arrow.h"
#include "EventStep.h"

Arrow::Arrow(df::Vector player_pos) {

	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
	// Set other object properties.
	setType("Arrow");

    setSprite("ArrowLeft");
	// Set starting location, based on hero's position passed in.
	df::Vector p(player_pos.getX() + 3, player_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);

    registerInterest(df::STEP_EVENT);
}

int Arrow::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        setVelocity(getVelocity()+ df::Vector(0,0.004));
    }
        return 0;
}