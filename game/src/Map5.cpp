#include "Map5.h"
#include "WorldManager.h"
#include "Map0.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "Map4.h"
#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

Map5::Map5(int difficulty, df::Music *p_music, int endingNumber, int playTime) {
	setType("Map5");
	this->difficulty = difficulty;
	this->p_music = p_music;
	this->endingNumber = endingNumber;
	this->playTime = playTime;
	registerInterest(df::KEYBOARD_EVENT);
	start();
}

Map5::~Map5() {}

void Map5::start() {
	std::fstream myFile;
	myFile.open("../game/easyScoreBoard.txt", std::ios::in);
	if (myFile.is_open()) {
		std::string line;
		int lineCount = 0;
		while (getline(myFile, line)) {
			float score = static_cast<float>(std::stoi(line));
			scoreListEasy[lineCount] = score / 10;
			lineCount++;
		}
		myFile.close();
	} else {
		LM.writeLog("Error: Easy scoreboard not found");
	}

	myFile.open("../game/normalScoreBoard.txt", std::ios::in);
	if (myFile.is_open()) {
		std::string line;
		int lineCount = 0;
		while (getline(myFile, line)) {
			float score = static_cast<float>(std::stoi(line));
			scoreListNormal[lineCount] = score / 10;
			lineCount++;
		}
		myFile.close();
	} else {
		LM.writeLog("Error: Normal scoreboard not found");
	}

	myFile.open("../game/difficultScoreBoard.txt", std::ios::in);
	if (myFile.is_open()) {
		std::string line;
		int lineCount = 0;
		while (getline(myFile, line)) {
			float score = static_cast<float>(std::stoi(line));
			scoreListDifficult[lineCount] = score / 10;
			lineCount++;
		}
		myFile.close();
	} else {
		LM.writeLog("Error: Difficult scoreboard not found");
	}
}

int Map5::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			RM.getSound("Hover")->play();
			if (p_keyboard_event->getKey() == df::Keyboard::Q) {
				p_music->stop();
				GM.setGameOver(true);
			} else if (p_keyboard_event->getKey() == df::Keyboard::R) {
				p_music->stop();
				WM.markForDelete(WM.getAllObjects());
				new Map0(difficulty);
			} else if (p_keyboard_event->getKey() == df::Keyboard::SPACE) {
				new Map4(difficulty, p_music, endingNumber, playTime);
				delete this;
			}
		}
	}
	return 0;
}

int Map5::draw() {

	DM.drawString(df::Vector(40, 8), "Scoreboard", df::CENTER_JUSTIFIED, df::CYAN);

	DM.drawString(df::Vector(20, 14), "Easy", df::CENTER_JUSTIFIED, df::WHITE);
	DM.drawString(df::Vector(40, 14), "Normal", df::CENTER_JUSTIFIED, df::YELLOW);
	DM.drawString(df::Vector(60, 14), "Difficult", df::CENTER_JUSTIFIED, df::RED);

	for (int i = 0; i < 3; i++) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << scoreListEasy[i];
		std::string s = stream.str();
		DM.drawString(df::Vector(20, 16 + 2 * i), s + "seconds", df::CENTER_JUSTIFIED, df::WHITE);
	}

	for (int i = 0; i < 3; i++) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << scoreListNormal[i];
		std::string s = stream.str();
		DM.drawString(df::Vector(40, 16 + 2 * i), s + "seconds", df::CENTER_JUSTIFIED, df::YELLOW);
	}

	for (int i = 0; i < 3; i++) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << scoreListDifficult[i];
		std::string s = stream.str();
		DM.drawString(df::Vector(60, 16 + 2 * i), s + "seconds", df::CENTER_JUSTIFIED, df::RED);
	}

	// keyboard hints
	DM.drawString(df::Vector(40, 28), "hit R to replay, hit q to quit", df::CENTER_JUSTIFIED,
	              df::Color::WHITE);
	DM.drawString(df::Vector(40, 29), "hit SPACE to show ending", df::CENTER_JUSTIFIED,
	              df::Color::WHITE);

	if (playTime != -1 && 10 <= endingNumber && endingNumber < 20) {
		float time = static_cast<float>(playTime) / 10;
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << time;
		std::string s = stream.str();
		DM.drawString(df::Vector(5, 1), "Play Time:" + s + 's', df::LEFT_JUSTIFIED, df::WHITE);
	}

	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(40, 1), "easy", df::CENTER_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(40, 1), "Normal", df::CENTER_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(40, 1), "DIFFICULT", df::CENTER_JUSTIFIED, df::RED);

	return Object::draw();
}
