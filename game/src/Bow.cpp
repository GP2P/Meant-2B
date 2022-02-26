#include "Bow.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"

Bow::Bow(df::Vector location) {
	setSolidness(df::SOFT);
	setType("Bow");
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

int Bow::eventHandler(const df::Event *p_e) {
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
					player->setHaveBow(true);
					WM.markForDelete(this);
				}
				break;
			case df::Keyboard::SLASH:
				if (nearPlayer && player->getID() == 2 && !player->haveItem()) {
					player->setHaveBow(true);
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

int Bow::draw() {
	DM.drawCh(getPosition() - df::Vector(0.6, 0), '|', df::WHITE);
	DM.drawCh(getPosition(), ')', df::YELLOW);

	if (nearPlayer) {
		if (player->getID() == 1) {
			if (!player->haveItem()) {
				DM.drawString(getPosition() - df::Vector(0, 4), "Press E to carry", df::CENTER_JUSTIFIED, df::WHITE);
			} else {
				DM.drawString(getPosition() - df::Vector(0, 4), "Can't carry more than 1 item", df::CENTER_JUSTIFIED,
				              df::WHITE);
			}
		}
		if (player->getID() == 2) {
			if (!player->haveItem()) {
				DM.drawString(getPosition() - df::Vector(0, 4), "Press Slash to carry", df::CENTER_JUSTIFIED,
				              df::WHITE);
			} else {
				DM.drawString(getPosition() - df::Vector(0, 4), "Can't carry more than 1 item", df::CENTER_JUSTIFIED,
				              df::WHITE);
			}
		}
	}
	return 1;
}
