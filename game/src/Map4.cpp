#include "Map4.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "GameManager.h"
#include "EventKeyboard.h"
#include "Map0.h"
#include "Block.h"

Map4::Map4(int difficulty, int endingNum) {
	this->difficulty = difficulty;
	endingNumber = endingNum;
	setType("Map4");
	setSprite("Map4BG");
	countDown = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	setLocation(df::CENTER_CENTER);
	setAltitude(0);
	registerInterest(df::KEYBOARD_EVENT);
	p_music = RM.getMusic("Map4BGM");
	p_music->play();
	buildBlocks(df::Vector(-100, 32), df::Vector(180, 32), '#'); // bottom
}

Map4::~Map4() {
	p_music->stop();
}

int Map4::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		if (p_keyboard_event->getKey() == df::Keyboard::Q)
			GM.setGameOver(true);
		else if (p_keyboard_event->getKey() == df::Keyboard::R &&
		         p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			WM.markForDelete(WM.getAllObjects());
			new Map0(difficulty);
		} else if (p_keyboard_event->getKey() == df::Keyboard::SPACE &&
		           p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			delete this;
		}
	}
	return 0;
}

int Map4::draw() {
	switch (endingNumber) {
		case 1: // both alive
			DM.drawString(df::Vector(39, 20), "You have defeated the illuminati!", df::CENTER_JUSTIFIED,
			              df::Color::WHITE);
			break;
		case 2: // bow alive
			break;
		case 3: // wand alive, bow died from bats
			break;
		case 4: // bow alive, wand died
			break;
		case 5: // bow alive, but escaped
			break;
		default:
			DM.drawString(df::Vector(39, 20), "Congratulations! You made it!", df::CENTER_JUSTIFIED, df::WHITE);
			break;
	}

	DM.drawString(df::Vector(39, 25), "hit R to replay, hit q to quit", df::CENTER_JUSTIFIED,
	              df::Color::WHITE);
	DM.drawString(df::Vector(39, 24), "hit SPACE to show scoreboard", df::CENTER_JUSTIFIED,
	              df::Color::WHITE);

	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(78, 1), "easy", df::RIGHT_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(78, 1), "Normal", df::RIGHT_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(78, 1), "DIFFICULT", df::RIGHT_JUSTIFIED, df::RED);

	return Object::draw();
}
