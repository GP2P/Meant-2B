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
	bowAlive = false;
	wandAlive = false;
	start();
}

Map3::~Map3() {
	p_music->stop();
}

void Map3::start() {
	p_music->play();

	// get status of players
	auto ol = WM.objectsOfType("Player");
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		auto *p_player = dynamic_cast<Player *>(oli.currentObject());
		if (p_player->isHaveWand()) {
			p_player->setHaveWand(false);
			wandAlive = true;
		}
		if (p_player->isHaveBow()) {
			p_player->setHaveBow(true);
			bowAlive = true;
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

	if (bowAlive) {
		// cage
		buildBlocks(df::Vector(64, 6), df::Vector(78, 6), ':', df::GREEN, 'c'); // top
		buildBlocks(df::Vector(71, 1), df::Vector(71, 6), '8', df::BLUE, 'c'); // chain
		buildBlocks(df::Vector(64, 11), df::Vector(78, 11), ':', df::GREEN, 'c'); // bottom
		buildBlocks(df::Vector(63, 7), df::Vector(64, 10), ':', df::GREEN, 'c'); // left

		// lever
		new Lever(df::Vector(78, 9));
	} else {
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
	new Boss();

	DM.shake(20, 20, 10);
}

void Map3::stop() {
	auto ol = df::ObjectList(WM.getAllObjects());
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		if (oli.currentObject()->getType() == "Player") {
			auto *p_player = dynamic_cast<Player *>(oli.currentObject());
			if (p_player->getPlayerID() == 1)
				oli.currentObject()->setPosition(df::Vector(39, 28));
			else
				oli.currentObject()->setPosition(df::Vector(69, 28));
			p_player->setMapNum(3);
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
	if (bowAlive) {
		DM.drawString(df::Vector(78, 13), "Defeat the illuminati", df::RIGHT_JUSTIFIED, df::WHITE);
		DM.drawString(df::Vector(78, 14), "with your bow!", df::RIGHT_JUSTIFIED, df::WHITE);
	}
	if (wandAlive && bowAlive)
		DM.drawString(df::Vector(39, 26), "The wand was taken from you... Stay alive!", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
	if (wandAlive && !bowAlive) {

		DM.drawString(df::Vector(39, 26), "The wand was taken from you...", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
		DM.drawString(df::Vector(39, 27), "Defeat the illuminati with this completely normal bow!",
		              df::CENTER_JUSTIFIED,
		              df::WHITE);
	}

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
