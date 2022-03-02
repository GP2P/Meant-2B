#include "BossPart.h"
#include "EventStep.h"

BossPart::BossPart(Boss *Boss) {
	boss = Boss;
	setSolidness(df::SPECTRAL);
	setAltitude(4);
	setSprite("BossPart");
	setPosition(boss->getPosition());
	registerInterest(df::STEP_EVENT);
}

int BossPart::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		setPosition(boss->getPosition());
		return 1;
	}
	return 0;
}