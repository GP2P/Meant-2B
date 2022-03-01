#include "Boss2.h"
#include "EventStep.h"

Boss2::Boss2(Boss *Boss) {
	boss = Boss;
	setSolidness(df::SPECTRAL);
	setAltitude(4);
	setSprite("Boss2");
	setPosition(boss->getPosition());
	registerInterest(df::STEP_EVENT);
}

int Boss2::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		setPosition(boss->getPosition());
		return 1;
	}
	return 0;
}