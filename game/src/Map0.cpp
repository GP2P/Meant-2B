#include "Map0.h"
#include "Object.h"
#include "ViewObject.h"
#include "ResourceManager.h"
#include "EventKeyboard.h"
#include "WorldManager.h"
#include "Map1.h"
#include "GameManager.h"

Map0::Map0() {
	setType("Map0");
	setSprite("Click2Start");
	setLocation(df::CENTER_CENTER);
	p_music = RM.getMusic("Map0BGM");
	p_music->play();
	registerInterest(df::KEYBOARD_EVENT);
	start();
}

Map0::~Map0() {
	p_music->stop();
	new Map1();
}

void Map0::start() {
}

int Map0::draw() {
	return df::Object::draw();
}

int Map0::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		if (p_keyboard_event->getKey() == df::Keyboard::SPACE) {
			p_music->pause();
			WM.markForDelete(this);
		}
		if (p_keyboard_event->getKey() == df::Keyboard::Q)
			GM.setGameOver();
		return 1;
	}
	return 0;
}
