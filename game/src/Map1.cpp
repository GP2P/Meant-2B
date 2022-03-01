#include "Map1.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Block.h"
#include "Player.h"
#include "PressurePlate.h"
#include "Gate.h"
#include "Inventory.h"
#include "Stone.h"
#include "Map2.h"

Map1::Map1(int difficulty) {
	this->difficulty = difficulty;
	setType("Map1");
	setSprite("Map1BG");
	setLocation(df::CENTER_CENTER);
	setAltitude(0);
	p_music = RM.getMusic("Map1BGM");
	start();
}

Map1::~Map1() {
	p_music->stop();
}

void Map1::start() {
	p_music->play();

	// map borders
	buildBlocks(df::Vector(0, 31), df::Vector(159, 31), '#');
	buildBlocks(df::Vector(0, 0), df::Vector(0, 31), '|');
	buildBlocks(df::Vector(79, 0), df::Vector(79, 23), '|');

	// platforms
	buildBlocks(df::Vector(1, 7), df::Vector(35, 7), '#');
	buildBlocks(df::Vector(44, 7), df::Vector(78, 7), '#');

	buildBlocks(df::Vector(8, 13), df::Vector(78, 13), '#');

	buildBlocks(df::Vector(1, 19), df::Vector(71, 19), '#');

	buildBlocks(df::Vector(8, 24), df::Vector(159, 24), '#');

	// end of map
	buildBlocks(df::Vector(159, 24), df::Vector(159, 31), '|');

	// gate 1
	new PressurePlate(df::Vector(25, 12), df::WHITE, 2);
	new Gate(df::Vector(15, 12), UP, df::WHITE);
	new PressurePlate(df::Vector(15, 18), df::WHITE, 2);

	// gate 2
	new PressurePlate(df::Vector(54, 18), df::YELLOW, 2);
	new Gate(df::Vector(64, 18), UP, df::YELLOW);
	new Stone(df::Vector(64, 23));

	auto *player1 = new Player(1);
	auto *player2 = new Player(2);
	player1->setPosition(df::Vector(15, 2));
	player2->setPosition(df::Vector(63, 2));
	player1->setMapNum(1);
	player2->setMapNum(1);
}

void Map1::stop() {
	auto ol = df::ObjectList(WM.getAllObjects());
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		if (oli.currentObject()->getType() == "Player") {
			// prevent players from getting back and teleported to the void
			if (oli.currentObject()->getPosition().getX() > 80)
				oli.currentObject()->setPosition(oli.currentObject()->getPosition() + df::Vector(-80, 0));
			auto *p_player = dynamic_cast<Player *>(oli.currentObject());
			p_player->setMapNum(2);
		} else if (oli.currentObject()->getType() == "Map1") {
			// do nothing to prevent double delete
		} else
			WM.markForDelete(oli.currentObject());
		oli.next();
	}
	new Map2(difficulty);
	delete this;
}

int Map1::draw() {
	// hint
	auto ol = df::ObjectList(WM.objectsOfType("Player"));
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		auto *p_player = dynamic_cast<Player *>(oli.currentObject());
		if (p_player->getPosition().getY() < 8)
			p_player->getPlayerID() == 1
			? DM.drawString(df::Vector(15, 2), "Move/jump with W, A, and D", df::CENTER_JUSTIFIED, df::WHITE)
			: DM.drawString(df::Vector(63, 2), "Move/jump with the arrow keys", df::CENTER_JUSTIFIED, df::WHITE);
		oli.next();
	}

	return Object::draw();
}
