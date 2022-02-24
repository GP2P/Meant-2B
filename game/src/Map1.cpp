#include "Map1.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Block.h"
#include "Player.h"
#include "DisplayManager.h"
#include <iostream>

Map1::Map1() {
	setType("Map1");
	setSprite("Map1BG");
	setLocation(df::CENTER_CENTER);
	p_music = RM.getMusic("Map1BGM");
	start();
}

void Map1::start() {
	p_music->play();

	for (int i = 0; i <= 80; i++) {
		new Block(df::Vector(i, 0));
		new Block(df::Vector(i, 23));
	}
	for (int i = 24; i >= 0; i--) {
		new Block(df::Vector(0, i));
		new Block(df::Vector(79, i));
	}

	new Block(df::Vector(50, 20));
	new Block(df::Vector(51, 20));
	new Block(df::Vector(52, 20));
	new Block(df::Vector(53, 20));
	new Block(df::Vector(54, 20));
	new Block(df::Vector(55, 20));
	new Block(df::Vector(56, 20));
	new Block(df::Vector(57, 20));
	new Block(df::Vector(58, 20));
	new Block(df::Vector(59, 20));
	new Block(df::Vector(60, 20));
	new Block(df::Vector(50, 21));
	new Block(df::Vector(52, 21));
	new Block(df::Vector(54, 21));
	new Block(df::Vector(56, 21));
	new Block(df::Vector(58, 21));
	new Block(df::Vector(60, 21));
	new Block(df::Vector(62, 19));
	new Block(df::Vector(62, 18));
	new Block(df::Vector(62, 17));
	new Block(df::Vector(62, 16));


	new Block(df::Vector(12, 20));
	new Block(df::Vector(15, 19));
	new Block(df::Vector(20, 18));


	auto *player1 = new Player;
	player1->setPosition(df::Vector(15, 10));

	WM.markForDelete(this);
}

int Map1::draw() {
	df::Object::draw();
	return 0;
}