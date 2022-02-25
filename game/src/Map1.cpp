#include "Map1.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Block.h"
#include "Player.h"
#include "PressurePlate.h"
#include "Gate.h"
#include "Inventory.h"

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
	buildBlocks(df::Vector(79, 0), df::Vector(79, 31), '|');

	// platform
	buildBlocks(df::Vector(0, 5), df::Vector(35, 5), '#');
	buildBlocks(df::Vector(44, 5), df::Vector(79, 5), '#');

	new PressurePlate(df::Vector(56, 19), df::BLUE, 10);
	new Gate(df::Vector(52, 16), RIGHT, df::BLUE);

	auto *player1 = new Player;
	player1->setPosition(df::Vector(10, 2));

	new Inventory;

	WM.markForDelete(this);
}

int Map1::draw() {
	df::Object::draw();
	return 0;
}
