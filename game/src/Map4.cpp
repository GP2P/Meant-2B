#include "Map4.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "GameManager.h"
#include "EventKeyboard.h"
#include "Map0.h"
#include "Block.h"
#include "Map5.h"

Map4::Map4(int difficulty, int endingNumber) {
	this->difficulty = difficulty;
	this->endingNumber = endingNumber;
	goodEnding = 10 <= endingNumber && endingNumber < 20;
	setType("Map4");
	setSprite("Map4BGBad");
	setLocation(df::CENTER_CENTER);
	setAltitude(0);
	registerInterest(df::KEYBOARD_EVENT);
	if (goodEnding)
		p_music = RM.getMusic("Map4BGMGood");
	else
		p_music = RM.getMusic("Map4BGMBad");
	p_music->play();
	buildBlocks(df::Vector(-100, 32), df::Vector(180, 32), '#'); // bottom
}

Map4::Map4(int difficulty, int endingNumber, int playTime) {
	this->playTime = playTime;
	this->difficulty = difficulty;
	this->endingNumber = endingNumber;
	goodEnding = 10 <= endingNumber && endingNumber < 20;
	setType("Map4");
	setSprite("Map4BGBad");
	setLocation(df::CENTER_CENTER);
	setAltitude(0);
	registerInterest(df::KEYBOARD_EVENT);
	if (goodEnding)
		p_music = RM.getMusic("Map4BGMGood");
	else
		p_music = RM.getMusic("Map4BGMBad");
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
			new Map5(difficulty, p_music);
		}
	}
	return 0;
}

int Map4::draw() {
	switch (endingNumber) {
		case 10: // both alive
			DM.drawString(df::Vector(40, 20),
			              "You have defeated the illuminati together!",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			break;
		case 11: // player 2 died in map 2, player 1 defeated boss
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You have defeated the illuminati!",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But at what cost?",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "Your girlfriend died for it...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			break;
		case 12: // player 1 died in map 2, player 2 defeated boss
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You have defeated the illuminati!",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But at what cost?",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "Your boyfriend died for it...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			break;
		case 13:  // boss killed player 2, player 1 killed boss
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "The illuminati held you hostage and killed your boyfriend",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But you avenged him with your bow",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "Rest in peace...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 14:  // boss killed player 1, player 2 killed boss
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "The illuminati held you hostage and killed your girlfriend",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But you avenged her with your bow",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "Rest in peace...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 21: // both reach boss, one player 2 died so player 1 escaped // unreachable cuz when ground player dies, player 2 goes to ground
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "The illuminati held you hostage and killed your girlfriend",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "You found a way out of the dungeon and escaped,",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "but she remained there and died along",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "Guess you weren't... meant to be... after all...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 22: // both reach boss, one player 1 died so player 2 escaped // unreachable cuz when ground player dies, player 2 goes to ground
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "The illuminati held you hostage and killed your boyfriend",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "You found a way out of the dungeon and escaped,",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "but he remained there and died along",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "Guess you weren't... meant to be... after all...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 23: // both reach boss, player 1 abandoned player 2 to be killed by the illuminati
			DM.drawString(df::Vector(40, 20), "Ending 5/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You betrayed your girlfriend and escaped,",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "leaving her die alone from the illuminati,",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "but maybe that's the best way...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "Guess you weren't... meant to be... after all...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 24: // both reach boss, player 2 abandoned player 1 to be killed by the illuminati
			DM.drawString(df::Vector(40, 20), "Ending 6/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You betrayed your boyfriend and escaped,",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "leaving him die alone from the illuminati,",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "but maybe that's the best way...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "Guess you weren't... meant to be... after all...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 30: // both died in map 2
			DM.drawString(df::Vector(40, 20), "Ending 0/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You both died from the bats when trying to escape",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But at least you didn't die alone...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "and didn't have to suffer the illuminati's wrath...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "You are meant to be... together... dead...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 31: // both died in map 3, player 1 died first
			DM.drawString(df::Vector(40, 20), "Ending 0/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You both died from the encounter with the illuminati",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But at least you didn't die alone...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "The girl did not betray, you are meant to be...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "together",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 32: // both died in map 3, player 2 died first
			DM.drawString(df::Vector(40, 20), "Ending 0/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "You both died from the encounter with the illuminati",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "But at least you didn't die alone...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "The boy did not betray, you are meant to be...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "together",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 33: // player 1 died in map 3, player 2 died in map 2
			DM.drawString(df::Vector(40, 20), "Ending 0/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "Your girlfriend died from the bats",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "you continued fighting, but died from the illuminati",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "You both died alone...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "Guess you weren't... meant to be... after all...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		case 34: // player 2 died in map 3, player 1 died in map 2
			DM.drawString(df::Vector(40, 20), "Ending 0/6",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			DM.drawString(df::Vector(40, 21), "Your boyfriend died from the bats",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 22), "you continued fighting, but died from the illuminati",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 23), "You both died alone...",
			              df::CENTER_JUSTIFIED, df::Color::WHITE);
			DM.drawString(df::Vector(40, 24), "Guess you weren't... meant to be... after all...",
			              df::CENTER_JUSTIFIED, df::Color::RED);
			break;
		default:
			DM.drawString(df::Vector(40, 20), "Congratulations! You made it!", df::CENTER_JUSTIFIED, df::WHITE);
			break;
	}

	DM.drawString(df::Vector(40, 28), "hit R to replay, hit q to quit", df::CENTER_JUSTIFIED,
	              df::Color::WHITE);
	DM.drawString(df::Vector(40, 29), "hit SPACE to show scoreboard", df::CENTER_JUSTIFIED,
	              df::Color::WHITE);

	if (playTime != -1 && goodEnding)
		DM.drawString(df::Vector(5, 1), "Play Time:" + std::to_string(playTime) + 's', df::LEFT_JUSTIFIED, df::WHITE);

	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(40, 1), "easy", df::CENTER_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(40, 1), "Normal", df::CENTER_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(40, 1), "DIFFICULT", df::CENTER_JUSTIFIED, df::RED);

	return Object::draw();
}
