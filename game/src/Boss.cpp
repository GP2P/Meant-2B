#include "Boss.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "LogManager.h"

Boss::Boss() {
	setType("Boss");
	setSprite("Boss");
	setPosition(df::Vector(10, 10));
    moveCountdown = 30;
    registerInterest(df::STEP_EVENT);
}

int Boss::eventHandler(const df::Event *p_e) {

    if (p_e->getType() == df::STEP_EVENT) {
        if(moveCountdown > 0){
            moveCountdown--;
        } else{
            int x = rand() % (DM.getHorizontal()-10) +5;
            int y = rand() % (DM.getVertical()-28) +5;
            df::Vector direction(x,y);
            direction = (direction - getPosition());
            direction.normalize();
            direction.scale(0.5);
            setVelocity(direction);
            moveCountdown = 30;
        }
        return 1;
    }
}
