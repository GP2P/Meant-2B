#include "Map3.h"
#include "ResourceManager.h"
#include "Block.h"
#include "DisplayManager.h"
#include "Boss.h"
#include "WorldManager.h"
#include "Player.h"
#include "Lever.h"
#include "Bow.h"
#include "Map4.h"

Map3::Map3(int difficulty) {
	this->difficulty = difficulty;
	setType("Map3");
	setSprite("Map3BG");
	setLocation(df::CENTER_CENTER);
	setAltitude(0);
	p_music = RM.getMusic("Map3BGM");
	start();
}

Map3::~Map3() {
	p_music->stop();
}

void Map3::start() {
	p_music->play();

	// initialize status of players
	auto ol = WM.objectsOfType("Player");
	auto oli = df::ObjectListIterator(&ol);

	// get player count and check if they have bow and wand
	while (!oli.isDone()) {
		playerCount++;

		// make sure only one player has bow, and only one player has wand
		auto *p_player = dynamic_cast<Player *>(oli.currentObject());
		if (p_player->isHaveBow()) {
			if (!haveBow) {
				haveBow = true;
			} else {
				// handle if both player has bow by error
				p_player->setHaveBow(false);
				p_player->setHaveWand(true);
				haveWand = true;
			}
		} else if (p_player->isHaveWand()) {
			if (!haveWand)
				haveWand = true;
			else {
				// handle if both player has wand by error
				p_player->setHaveWand(false);
				p_player->setHaveBow(true);
				haveBow = true;
			}
		}
		oli.next();
	}

	// sets player position
	oli.first();
	while (!oli.isDone()) {
		auto *p_player = dynamic_cast<Player *>(oli.currentObject());
		p_player->setMapNum(3);

		if (playerCount == 2) {
			if (haveWand) {
				if (p_player->isHaveWand())
					oli.currentObject()->setPosition(df::Vector(39, 28)); // ground
				else {
					p_player->setHaveBow(true); // to show reticle
					oli.currentObject()->setPosition(df::Vector(71, 8)); // cage
				}
			} else if (haveBow) {
				if (p_player->isHaveBow()) {
					p_player->setHaveBow(true); // to show reticle
					oli.currentObject()->setPosition(df::Vector(71, 8)); // cage
				} else {
					// already know haveWand == false
					p_player->setHaveWand(true);
					oli.currentObject()->setPosition(df::Vector(39, 28)); // ground
				}
			} else {
				if (p_player->getPlayerID() == 1) {
					p_player->setHaveWand(true);
					oli.currentObject()->setPosition(df::Vector(39, 28)); // ground
				} else {
					p_player->setHaveBow(true);
					oli.currentObject()->setPosition(df::Vector(71, 8)); // cage
				}
			}
		} else if (playerCount == 1) {
			if (haveBow)
				p_player->setHaveBow(true);

			oli.currentObject()->setPosition(df::Vector(39, 28)); // ground
		}

		// remove wand
		if (p_player->isHaveWand()) {
			p_player->setHaveWand(false);
		}

		oli.next();
	}

	// map borders
	buildBlocks(df::Vector(0, 0), df::Vector(79, 0), '#'); // top
	buildBlocks(df::Vector(0, 31), df::Vector(79, 31), '#'); // bottom
	buildBlocks(df::Vector(0, 1), df::Vector(0, 30), '|'); // left
	buildBlocks(df::Vector(79, 1), df::Vector(79, 6), '|'); // right1
	buildBlocks(df::Vector(79, 7), df::Vector(79, 10), '2'); // door
	buildBlocks(df::Vector(79, 11), df::Vector(79, 30), '|'); // right2

	if (playerCount == 2) {
		// cage
		buildBlocks(df::Vector(64, 6), df::Vector(78, 6), ':', df::GREEN, 'c'); // top
		buildBlocks(df::Vector(71, 1), df::Vector(71, 6), '8', df::BLUE, 'c'); // chain
		buildBlocks(df::Vector(64, 11), df::Vector(78, 11), ':', df::GREEN, 'c'); // bottom
		buildBlocks(df::Vector(63, 7), df::Vector(64, 10), ':', df::GREEN, 'c'); // left

		// lever
		new Lever(df::Vector(78, 9));
	} else if (playerCount == 1 && !haveBow) {
		// altar
		new Block(df::Vector(22, 30), '\\', df::GREEN, 'a');
		new Block(df::Vector(23, 30), '_', df::GREEN, 'a');
		new Block(df::Vector(24, 30), '_', df::GREEN, 'a');
		new Block(df::Vector(25, 30), '/', df::GREEN, 'a');

		// bow
		new Bow(df::Vector(24, 29));
	}

	// escape door
	p_escapeDoor[0] = new Block(df::Vector(79, 7), '|');
	p_escapeDoor[1] = new Block(df::Vector(79, 8), '|');
	p_escapeDoor[2] = new Block(df::Vector(79, 9), '|');
	p_escapeDoor[3] = new Block(df::Vector(79, 10), '|');

	// boss
	new Boss(difficulty);

	DM.shake(20, 20, 10);
}

void Map3::stop() {
	auto ol = df::ObjectList(WM.getAllObjects());
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		if (oli.currentObject()->getType() == "Player") {
			auto *p_player = dynamic_cast<Player *>(oli.currentObject());
			p_player->setMapNum(4);
			if (p_player->getPlayerID() == 1)
				oli.currentObject()->setPosition(df::Vector(39, 28));
			else
				oli.currentObject()->setPosition(df::Vector(69, 28));
			if (p_player->isHaveBow())
				p_player->setHaveBow(false);
			else
				p_player->setHaveWand(true);
		} else if (oli.currentObject()->getType() == "Map3") {
			// do nothing to prevent double delete
		} else
			WM.markForDelete(oli.currentObject());
		oli.next();
	}
	new Map4(difficulty, 0);
	delete this;
}

int Map3::draw() {
	// draw player hints
	if (playerCount == 2) {
		DM.drawString(df::Vector(78, 13), "Defeat the illuminati", df::RIGHT_JUSTIFIED, df::WHITE);
		DM.drawString(df::Vector(78, 14), "with your bow!", df::RIGHT_JUSTIFIED, df::WHITE);
		DM.drawString(df::Vector(39, 26), "The wand was taken from you... Stay alive!", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
	}
	if (playerCount == 1 && haveBow) {
		DM.drawString(df::Vector(39, 27), "Defeat the illuminati... with your completely normal bow!",
		              df::CENTER_JUSTIFIED, df::WHITE);
	}
	if (playerCount == 1 && !haveBow) {
		DM.drawString(df::Vector(39, 26), "The wand was taken from you...", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
		DM.drawString(df::Vector(39, 27), "Defeat the illuminati with this completely normal bow!",
		              df::CENTER_JUSTIFIED, df::WHITE);
	}

	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(78, 1), "easy", df::RIGHT_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(78, 1), "Normal", df::RIGHT_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(78, 1), "DIFFICULT", df::RIGHT_JUSTIFIED, df::RED);

	return Object::draw();
}

void Map3::escape() {
	for (auto &i: p_escapeDoor) {
		i->setSolidness(df::SOFT);
		i->setColor(df::BLACK);
	}
}

int Map3::getDifficulty() const {
	return difficulty;
}
