#include "BossEye.h"
#include "EventStep.h"

BossEye::BossEye(Boss *Boss) {
	boss = Boss;
	setSolidness(df::SPECTRAL);
	setAltitude(4);
	setType("BossEye");
	setSprite("BossEye");
	setPosition(boss->getPosition());
	registerInterest(df::STEP_EVENT);
}

int BossEye::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		setPosition(boss->getPosition());
		return 1;
	}
	return 0;
}