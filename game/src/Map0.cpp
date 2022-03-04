#include "Map0.h"
#include "Object.h"
#include "ViewObject.h"
#include "ResourceManager.h"
#include "EventKeyboard.h"
#include "Map1.h"
#include "GameManager.h"
#include "DisplayManager.h"


Map0::Map0(int difficulty) {
	this->difficulty = difficulty;
	setType("Map0");
	setSprite("Map0BG");
	setLocation(df::CENTER_CENTER);
	p_music = RM.getMusic("Map0BGM");
	p_music->play();
	registerInterest(df::KEYBOARD_EVENT);
}

Map0::~Map0() {}

int Map0::draw() {
	// difficulty selection
	DM.drawString(df::Vector(40, 24), "'E' for easy", df::CENTER_JUSTIFIED, difficulty == 0 ? df::YELLOW : df::WHITE);
	DM.drawString(df::Vector(40, 26), "'N' for normal", df::CENTER_JUSTIFIED, difficulty == 1 ? df::YELLOW : df::WHITE);
	DM.drawString(df::Vector(40, 28), "'D' for difficult", df::CENTER_JUSTIFIED,
	              difficulty == 2 ? df::YELLOW : df::WHITE);

	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(40, 1), "easy", df::CENTER_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(40, 1), "Normal", df::CENTER_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(40, 1), "DIFFICULT", df::CENTER_JUSTIFIED, df::RED);

	return df::Object::draw();
}

int Map0::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			if (p_keyboard_event->getKey() == df::Keyboard::SPACE) {
				RM.getSound("Hover")->play();
				new Map1(difficulty, p_music);
				delete this;
			}
			if (p_keyboard_event->getKey() == df::Keyboard::X) {
				RM.getSound("Hover")->play();
				GM.setGameOver(true);
			}
			if (p_keyboard_event->getKey() == df::Keyboard::E) { // easy mode
				RM.getSound("Hover")->play();
				difficulty = 0;
			}
			if (p_keyboard_event->getKey() == df::Keyboard::N) { // normal mode
				RM.getSound("Hover")->play();
				difficulty = 1;
			}
			if (p_keyboard_event->getKey() == df::Keyboard::D) { // difficult mode
				RM.getSound("Hover")->play();
				difficulty = 2;
			}
			return 1;
		}
	}
	return 0;
}
