#include "Boss.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "BossProjectile.h"

#include <math.h>

Boss::Boss() {
	setType("Boss");
	setSprite("Boss");
	setPosition(df::Vector(10, 10));
	moveCountdown = 30;
	registerInterest(df::STEP_EVENT);
	setSolidness(df::SOFT);
    hp  = 5;
    fireSlowdown = 60;
    fireCountdown = fireSlowdown;
	hp = 5;
}

int Boss::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		if (hp <= 0) {
			WM.markForDelete(this);
		}

        bool withinX = (getPosition().getX() < DM.getHorizontal() - 3) && (getPosition().getX() > 3);
        bool withinY = (getPosition().getY() < DM.getVertical() - 7) && (getPosition().getY() > 2);
        bool outOfCage = (getPosition().getX()<64)||(getPosition().getY()>11);
		if (moveCountdown > 0 && withinX
		    && withinY && outOfCage) {
			moveCountdown--;
		} else {
			int x = rand() % (DM.getHorizontal() - 10) + 5;
			int y = rand() % (DM.getVertical() - 10) + 5;
			df::Vector direction(x, y);
			direction = (direction - getPosition());
			direction.normalize();
			direction.scale(0.5);
			setVelocity(direction);
			moveCountdown = 30;
		}

        if(fireCountdown<=0){
            fire();
            fireCountdown = fireSlowdown;
        } else{
            fireCountdown--;
        }
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if ((p_ce->getObject1()->getType() == "Player") ||
		    (p_ce->getObject2()->getType() == "Player")) {
			WM.markForDelete(p_ce->getObject1());
			WM.markForDelete(p_ce->getObject2());
			return 1;
		}
	}
	return 0;
}

int Boss::getHp() const {
	return hp;
}

void Boss::setHp(int Hp) {
	hp = Hp;
}

void Boss::fire(){
    LM.writeLog("shoot");
    auto b = new BossProjectile(getPosition());
    b->setVelocity(df::Vector(1,0));
}
