#include "Lever.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventGate.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "Player.h"
#include "EventKeyboard.h"
#include "Map2.h"

Lever::Lever() {}

Lever::Lever(df::Vector position) {
	setType("Lever");
	setSolidness(df::SOFT);
	setAltitude(3);
	setPosition(position);
	nearCountdown = 0;
	nearPlayer = false;
	player = nullptr;
	color = df::YELLOW;
	character = '/';
	registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::COLLISION_EVENT);
}

int Lever::draw() {
	DM.drawCh(getPosition() - df::Vector(0, 0.1), character, color);

	if (nearPlayer) {
		if (player->getID() == 1) {
			DM.drawString(getPosition() - df::Vector(0, 4), "Press E to pull lever", df::CENTER_JUSTIFIED, df::WHITE);
		}
		if (player->getID() == 2) {
			DM.drawString(getPosition() - df::Vector(0, 4), "Press slash to pull lever", df::CENTER_JUSTIFIED,
			              df::WHITE);
		}
	}
	return 1;
}

int Lever::eventHandler(const df::Event *p_e) {
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
				if (nearPlayer && player->getID() == 1) {
					character = '\\';
					auto m2l = df::ObjectList(WM.objectsOfType("Map2"));
					if (!m2l.isEmpty()) {
						auto mli = df::ObjectListIterator(&m2l);
						auto *p_Map2 = dynamic_cast<Map2 *>(mli.currentObject());
						p_Map2->stop();
					}
				}
				break;
			case df::Keyboard::SLASH:
				if (nearPlayer && player->getID() == 2) {
					character = '\\';
					auto m2l = df::ObjectList(WM.objectsOfType("Map2"));
					if (!m2l.isEmpty()) {
						auto mli = df::ObjectListIterator(&m2l);
						auto *p_Map2 = dynamic_cast<Map2 *>(mli.currentObject());
						p_Map2->stop();
					}
				}
				break;
			default:    // Key not included
				break;
		}
		return 1;
	}
}
