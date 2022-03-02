#include "BossPart.h"
#include "EventStep.h"
#include "LogManager.h"

BossPart::BossPart(Boss *Boss) {
	boss = Boss;
	setSolidness(df::SPECTRAL);
	setAltitude(4);
	setSprite("BossPart");
    setType("BossPart");
    setPosition(boss->getPosition());
	registerInterest(df::STEP_EVENT);
    stage = 1;
}

int BossPart::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
        if (stage == 2) {
            setPosition(boss->getPosition() + df::Vector(0, 1));
        } else{
            setPosition(boss->getPosition());
        }
		return 1;
	}
	return 0;
}

void BossPart::setStage(int stage) {
    BossPart::stage = stage;
}
