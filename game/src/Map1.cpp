#include "Map1.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Block.h"
#include "Player.h"
#include "PressurePlate.h"
#include "Gate.h"
#include "Inventory.h"
#include "Stone.h"

Map1::Map1() {
	setType("Map1");
	setSprite("Map1BG");
	setLocation(df::CENTER_CENTER);
	p_music = RM.getMusic("Map1BGM");
	start();
}

void Map1::start() {
	p_music->play();

	// map borders
	buildBlocks(df::Vector(0, 31), df::Vector(79, 31));
	buildBlocks(df::Vector(0, 0), df::Vector(0, 31), '|');
	buildBlocks(df::Vector(79, 0), df::Vector(79, 24), '|');

	// platforms
	buildBlocks(df::Vector(1, 7), df::Vector(35, 7), '#');
	buildBlocks(df::Vector(44, 7), df::Vector(78, 7), '#');

	buildBlocks(df::Vector(8, 13), df::Vector(78, 13), '#');

	buildBlocks(df::Vector(1, 19), df::Vector(71, 19), '#');

	buildBlocks(df::Vector(8, 24), df::Vector(78, 24), '#');

	// gate 1
	new PressurePlate(df::Vector(21, 12), df::WHITE, 2);

	new Gate(df::Vector(15, 12), UP, df::WHITE);
	new PressurePlate(df::Vector(15, 18), df::WHITE, 2);

    new Stone(df::Vector(21, 9));


    // gate 2
	new PressurePlate(df::Vector(58, 18), df::YELLOW, 2);
	new Gate(df::Vector(64, 18), UP, df::YELLOW);

	auto *player1 = new Player;
	player1->setPosition(df::Vector(10, 2));

	WM.markForDelete(this);
}

int Map1::draw() {
	df::Object::draw();
	return 0;
}
