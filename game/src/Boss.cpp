#include "Boss.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "BossProjectile.h"
#include "Boss2.h"
#include "BossEye.h"
#include "Map3.h"

#include <math.h>

Boss::Boss() {
	setType("Boss");
	setSprite("Boss");
	setPosition(df::Vector(10, 10));
	moveCountdown = 30;
	registerInterest(df::STEP_EVENT);
	setSolidness(df::SOFT);
	fireCountdown = fireSlowdown;
	hp = 5;
	new Boss2(this);
	new BossEye(this);
}

int Boss::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		if (hp <= 0) {
			auto ol = WM.objectsOfType("Map3");
			if (!ol.isEmpty()) {
				auto oli = df::ObjectListIterator(&ol);
				auto *p_map3 = dynamic_cast<Map3 *>(oli.currentObject());
				p_map3->stop();
			}
			WM.markForDelete(this);
		}

		bool withinX = (getPosition().getX() < DM.getHorizontal() - 3) && (getPosition().getX() > 3);
		bool withinY = (getPosition().getY() < DM.getVertical() - 7) && (getPosition().getY() > 2);
		bool outOfCage = (getPosition().getX() < 64) || (getPosition().getY() > 11);
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
			direction = df::Vector(direction.getX(), direction.getY() / 2);
			setVelocity(direction);
			moveCountdown = 30;
		}

		if (fireCountdown <= 0) {
			fire();
			fireCountdown = fireSlowdown;
		} else {
			fireCountdown--;
		}
		return 1;
	}
	return 0;
}

int Boss::getHp() const {
	return hp;
}

void Boss::setHp(int Hp) {
	hp = Hp;
}

void Boss::fire() {
	for (int i = 0; i <= 5; i++) {
		auto b = new BossProjectile(getPosition());
		df::Vector a(tan(1 + i * 17.5), 1);
		a.normalize();
		b->setDirection(a);
		b->setVelocity(df::Vector(b->getVelocity().getX(), b->getVelocity().getY() / 2));
	}
}
