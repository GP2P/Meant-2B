#include "Map3.h"
#include "ResourceManager.h"
#include "Block.h"
#include "DisplayManager.h"
#include "Boss.h"
#include "WorldManager.h"
#include "Player.h"
#include "Lever.h"

Map3::Map3() {
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

	auto *player1 = new Player(1);
	auto *player2 = new Player(2);
	player1->setPosition(df::Vector(71, 8));
	player1->setHaveBow(true);
	player2->setPosition(df::Vector(39, 28));
	player2->setHaveWand(true);

	// get status of players
	auto ol = WM.objectsOfType("Player");
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		auto *p_player = dynamic_cast<Player *>(oli.currentObject());
		if (p_player->isHaveBow())
			bowAlive = true;
		if (p_player->isHaveWand())
			wandAlive = true;
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
		buildBlocks(df::Vector(64, 6), df::Vector(78, 6), ':'); // top
		buildBlocks(df::Vector(71, 1), df::Vector(71, 6), '8', df::BLUE); // chain
		buildBlocks(df::Vector(64, 11), df::Vector(78, 11), ':'); // bottom
		buildBlocks(df::Vector(63, 7), df::Vector(64, 10), ':'); // left

		// lever
		new Lever(df::Vector(78, 9));
	}

	// escape door
	auto b1 = new Block(df::Vector(79, 7), '|');
	auto b2 = new Block(df::Vector(79, 8), '|');
	auto b3 = new Block(df::Vector(79, 9), '|');
	auto b4 = new Block(df::Vector(79, 10), '|');
	p_escapeDoor[0] = b1;
	p_escapeDoor[1] = b2;
	p_escapeDoor[2] = b3;
	p_escapeDoor[3] = b4;

	// boss
	new Boss();

	DM.shake(20, 20, 10);
}

void Map3::stop(int endingNum) {

}

int Map3::draw() {
	if (bowAlive) {
		DM.drawString(df::Vector(78, 13), "Defeat the illuminati", df::RIGHT_JUSTIFIED, df::WHITE);
		DM.drawString(df::Vector(78, 14), "with your bow!", df::RIGHT_JUSTIFIED, df::WHITE);
	}
	if (wandAlive)
		DM.drawString(df::Vector(39, 27), "The wand was taken from you... Stay alive!", df::CENTER_JUSTIFIED,
		              df::MAGENTA);
	return Object::draw();
}

void Map3::escape() {
	for (auto &i: p_escapeDoor) {
		i->setSolidness(df::SOFT);
		i->setColor(df::BLACK);
	}
}
