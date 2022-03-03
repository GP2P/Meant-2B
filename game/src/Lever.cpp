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
#include "Map3.h"
#include "ResourceManager.h"

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
		if (player->getPlayerID() == 1) {
			if (player->getMapNum() == 2)
				DM.drawString(getPosition() + df::Vector(0, -3), "Press E to pull", df::RIGHT_JUSTIFIED, df::YELLOW);
			else if (player->getMapNum() == 3)
				DM.drawString(getPosition() + df::Vector(0, -2), "Press E to pull", df::RIGHT_JUSTIFIED, df::YELLOW);
		}
		if (player->getPlayerID() == 2) {
			if (player->getMapNum() == 2)
				DM.drawString(getPosition() + df::Vector(0, -3), "Press slash to pull", df::RIGHT_JUSTIFIED,
				              df::YELLOW);
			else if (player->getMapNum() == 3)
				DM.drawString(getPosition() + df::Vector(0, -2), "Press slash to pull", df::RIGHT_JUSTIFIED,
				              df::YELLOW);
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
				if (nearPlayer && player->getPlayerID() == 1 &&
				    p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
					character = '\\';
					RM.getSound("Hover")->play();
					auto m2l = df::ObjectList(WM.objectsOfType("Map2"));
					if (!m2l.isEmpty()) {
						auto mli = df::ObjectListIterator(&m2l);
						auto *p_Map2 = dynamic_cast<Map2 *>(mli.currentObject());
						p_Map2->stop();
					} else {
						auto m3l = df::ObjectList(WM.objectsOfType("Map3"));
						auto mli = df::ObjectListIterator(&m3l);
						auto *p_Map3 = dynamic_cast<Map3 *>(mli.currentObject());
						p_Map3->escape();
					}
				}
				break;
			case df::Keyboard::SLASH:
				if (nearPlayer && player->getPlayerID() == 2 &&
				    p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
					character = '\\';
					RM.getSound("Hover")->play();
					auto m2l = df::ObjectList(WM.objectsOfType("Map2"));
					if (!m2l.isEmpty()) {
						auto mli = df::ObjectListIterator(&m2l);
						auto *p_Map2 = dynamic_cast<Map2 *>(mli.currentObject());
						p_Map2->stop();
					} else {
						auto m3l = df::ObjectList(WM.objectsOfType("Map3"));
						auto mli = df::ObjectListIterator(&m3l);
						auto *p_Map3 = dynamic_cast<Map3 *>(mli.currentObject());
						p_Map3->escape();
					}
				}
				break;
			default:    // Key not included
				break;
		}
		return 1;
	}
	return 0;
}
