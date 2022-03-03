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
				if (p_player->isHaveWand()) {
					p_player->setMap3OnGround(true);
					oli.currentObject()->setPosition(df::Vector(40, 28)); // ground
				} else {
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
					p_player->setMap3OnGround(true);
					oli.currentObject()->setPosition(df::Vector(40, 28)); // ground
				}
			} else {
				if (p_player->getPlayerID() == 1) {
					p_player->setHaveWand(true);
					p_player->setMap3OnGround(true);
					oli.currentObject()->setPosition(df::Vector(40, 28)); // ground
				} else {
					p_player->setHaveBow(true);
					oli.currentObject()->setPosition(df::Vector(71, 8)); // cage
				}
			}
		} else if (playerCount == 1) {
			if (haveBow)
				p_player->setHaveBow(true);

			p_player->setMap3OnGround(true);
			oli.currentObject()->setPosition(df::Vector(40, 28)); // ground
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
	buildBlocks(df::Vector(79, 11), df::Vector(79, 30), '|'); // right2

	if (playerCount == 2) {
		// cage
		buildBlocks(df::Vector(64, 6), df::Vector(78, 6), ':', df::GREEN, 'c'); // top
		buildBlocks(df::Vector(71, 1), df::Vector(71, 6), '8', df::BLUE, 'c'); // chain
		buildBlocks(df::Vector(63, 7), df::Vector(64, 10), ':', df::GREEN, 'c'); // left

		// cage floor
		p_cageFloor[0] = new Block(df::Vector(64, 11), ':', df::GREEN, 'c');
		p_cageFloor[1] = new Block(df::Vector(65, 11), ':', df::GREEN, 'c');
		p_cageFloor[2] = new Block(df::Vector(66, 11), ':', df::GREEN, 'c');
		p_cageFloor[3] = new Block(df::Vector(67, 11), ':', df::GREEN, 'c');
		p_cageFloor[4] = new Block(df::Vector(68, 11), ':', df::GREEN, 'c');
		p_cageFloor[5] = new Block(df::Vector(69, 11), ':', df::GREEN, 'c');
		p_cageFloor[6] = new Block(df::Vector(70, 11), ':', df::GREEN, 'c');
		p_cageFloor[7] = new Block(df::Vector(71, 11), ':', df::GREEN, 'c');
		p_cageFloor[8] = new Block(df::Vector(72, 11), ':', df::GREEN, 'c');
		p_cageFloor[9] = new Block(df::Vector(73, 11), ':', df::GREEN, 'c');
		p_cageFloor[10] = new Block(df::Vector(74, 11), ':', df::GREEN, 'c');
		p_cageFloor[11] = new Block(df::Vector(75, 11), ':', df::GREEN, 'c');
		p_cageFloor[12] = new Block(df::Vector(76, 11), ':', df::GREEN, 'c');
		p_cageFloor[13] = new Block(df::Vector(77, 11), ':', df::GREEN, 'c');
		p_cageFloor[14] = new Block(df::Vector(78, 11), ':', df::GREEN, 'c');

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

void Map3::stop(int type, int playTime) {
	auto ol = df::ObjectList(WM.getAllObjects());
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		if (oli.currentObject()->getType() == "Player") {
			auto *p_player = dynamic_cast<Player *>(oli.currentObject());
			p_player->setMapNum(4);
			if (p_player->getPlayerID() == 1)
				oli.currentObject()->setPosition(df::Vector(40, 28));
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


	auto pl = WM.objectsOfType("Player");
	auto pli = df::ObjectListIterator(&pl);
	switch (type) {
		case 0: // boss died (archer player did not escape)
			if (playerCount == 2) { // both player reached boss
				pli.next();
				if (pli.isDone()) { // but only one player left
					pli.first();
					if (dynamic_cast<Player *>(pli.currentObject())->getPlayerID() == 1)
						new Map4(difficulty, 13, playTime); // boss killed player 2, player 1 killed boss
					else
						new Map4(difficulty, 14, playTime); // boss killed player 1, player 2 killed boss
				} else { // both player survived
					new Map4(difficulty, 10, playTime);
				}
			} else { // one player died in map 2
				if (dynamic_cast<Player *>(pli.currentObject())->getPlayerID() == 1)
					// player 2 died in map 2, player 1 defeated boss
					new Map4(difficulty, 11, playTime);
				else
					// player 1 died in map 2, player 2 defeated boss
					new Map4(difficulty, 12, playTime);
			}
			break;
		case 1: // other player died, left
			if (dynamic_cast<Player *>(pli.currentObject())->getPlayerID() == 1) {
				new Map4(difficulty, 21, playTime); // both reach boss, one player2 died so player1 escaped
			} else if (dynamic_cast<Player *>(oli.currentObject())->getPlayerID() == 1) {
				new Map4(difficulty, 22, playTime); // both reach boss, one player1 died so player2 escaped
			}
			break;
		case 2: // abandoned other player
			if (dynamic_cast<Player *>(pli.currentObject())->getPlayerID() == 1) {
				new Map4(difficulty, 23,
				         playTime); // both reach boss, player1 abandoned player2 to be killed by the illuminati
			} else if (dynamic_cast<Player *>(oli.currentObject())->getPlayerID() == 1) {
				new Map4(difficulty, 24,
				         playTime); // both reach boss, player2 abandoned player1 to be killed by the illuminati
			}
			break;
		default:
			new Map4(difficulty, 10, playTime);
			break;
	}
	delete this;
}

int Map3::draw() {
	// draw player hints
	if (playerCount == 2) {
		DM.drawString(df::Vector(78, 13), "Defeat the illuminati", df::RIGHT_JUSTIFIED, df::WHITE);
		DM.drawString(df::Vector(78, 14), "with your bow!", df::RIGHT_JUSTIFIED, df::WHITE);
		DM.drawString(df::Vector(40, 26), "The wand was taken from you... Stay alive!", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
	}
	if (playerCount == 1 && haveBow) {
		DM.drawString(df::Vector(40, 27), "Defeat the illuminati... with your completely normal bow!",
		              df::CENTER_JUSTIFIED, df::WHITE);
	}
	if (playerCount == 1 && !haveBow) {
		DM.drawString(df::Vector(40, 26), "The wand was taken from you...", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
		DM.drawString(df::Vector(40, 27), "Defeat the illuminati with this completely normal bow!",
		              df::CENTER_JUSTIFIED, df::WHITE);
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

void Map3::escape() {
	for (auto &i: p_escapeDoor) {
		WM.markForDelete(i);
	}
	WM.markForDelete(WM.objectsOfType("Lever"));
}

void Map3::groundDefeat() {
	// remove cage floor
	for (auto &i: p_cageFloor) {
		WM.markForDelete(i);
	}

	// delete existing projectiles
	WM.markForDelete(WM.objectsOfType("BossProjectile"));
	WM.markForDelete(WM.objectsOfType("BossCrystal"));

	// mark player for on ground
	auto pl = WM.objectsOfType("Player");
	auto pli = df::ObjectListIterator(&pl);
	while (!pli.isDone()) {
		dynamic_cast<Player *>(pli.currentObject())->setMap3OnGround(true);
		pli.next();
	}
}

int Map3::getDifficulty() const {
	return difficulty;
}

int Map3::getPlayerCount() const {
	return playerCount;
}

void Map3::setPlayerCount(int playerCount) {
	Map3::playerCount = playerCount;
}
