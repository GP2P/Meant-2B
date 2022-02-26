#include "Stone.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"

Stone::Stone(df::Vector location) {
	setSolidness(df::SOFT);
	setType("Stone");
	setPosition(location);
	nearPlayer = false;
	player = nullptr;
	nearCountdown = 0;
	acceleration = df::Vector(0, 0.02);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	setBox(df::Box(df::Vector(-1.5, -1.5), 2.4, 2));
}

int Stone::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const auto *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if ((p_ce->getObject1()->getType() == "Player")) {
			auto *p = dynamic_cast <Player *> (p_ce->getObject1());
			nearPlayer = true;
			player = p;
			nearCountdown = 4;
			return 1;
		} else if (p_ce->getObject2()->getType() == "Player") {
			auto *p = dynamic_cast <Player *> (p_ce->getObject2());
			nearPlayer = true;
			player = p;
			nearCountdown = 4;
			return 1;
		}
	}
	if (p_e->getType() == df::STEP_EVENT) {
		if (!onGround()) setVelocity(getVelocity() + acceleration);
		else setVelocity(df::Vector(0, 0));
		nearCountdown--;
		if (nearCountdown <= 0) {
			nearPlayer = false;
			player = nullptr;
		}
		return 1;
	}

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		switch (p_keyboard_event->getKey()) {
			case df::Keyboard::E:
				if (nearPlayer && player->getID() == 1 && !player->haveItem()) {
					player->setHaveStone(true);
					WM.markForDelete(this);
				}
				break;
			case df::Keyboard::SLASH:
				if (nearPlayer && player->getID() == 2 && !player->haveItem()) {
					player->setHaveStone(true);
					WM.markForDelete(this);
				}
				break;
			default:    // Key not included
				break;
		}
		return 1;
	}
	return 0;
}

int Stone::draw() {
	DM.drawCh(getPosition(), '@', df::CYAN);
	if (nearPlayer) {
		if (player->getID() == 1) {
			DM.drawString(getPosition() - df::Vector(0, 4), "Press E to carry", df::CENTER_JUSTIFIED, df::WHITE);
		}
		if (player->getID() == 2) {
			DM.drawString(getPosition() - df::Vector(0, 4), "Press slash to carry", df::CENTER_JUSTIFIED, df::WHITE);
		}
	}
	return 1;
}

bool Stone::onGround() {
	df::ObjectList collisions = WM.getCollisions(this, getPosition() + getVelocity());
	bool on = false;
	// soft collisions don't count as on ground
	if (!collisions.isEmpty()) {
		auto oli = df::ObjectListIterator(&collisions);
		while (!oli.isDone()) {
			if (oli.currentObject()->getSolidness() == df::HARD)
				on = true;
			if (oli.currentObject()->getType() == "PressurePlate") {
				auto *p_ce = new df::EventCollision;
				p_ce->setObject1(oli.currentObject());
				p_ce->setObject2(this);
				oli.currentObject()->eventHandler(p_ce);
			}
			oli.next();
		}
		return on;
	} else return false;
}
