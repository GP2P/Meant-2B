#include "Map2.h"
#include "ResourceManager.h"
#include "Block.h"
#include "Player.h"
#include "Map3.h"
#include "Bat.h"
#include "Lever.h"
#include "Bow.h"
#include "Wand.h"
#include "DisplayManager.h"
#include "WorldManager.h"

Map2::Map2(int difficulty) {
	this->difficulty = difficulty;
	setType("Map2");
	setLocation(df::CENTER_CENTER);
	setAltitude(0);
	p_music = RM.getMusic("Map2BGM");
	start();
}

Map2::~Map2() {
	p_music->stop();
}

void Map2::start() {
	p_music->play();

	// map borders
	buildBlocks(df::Vector(1, -1), df::Vector(78, -1), '_'); // top
	buildBlocks(df::Vector(0, 31), df::Vector(79, 31), '#'); // bottom
	buildBlocks(df::Vector(0, 0), df::Vector(0, 24), '|'); // left
	buildBlocks(df::Vector(-1, 25), df::Vector(-1, 30), '|'); // door
	buildBlocks(df::Vector(79, 0), df::Vector(79, 30), '|'); // right

	// platforms
	buildBlocks(df::Vector(64, 4), df::Vector(78, 4), '#');

	// altars
	new Block(df::Vector(22, 30), '\\', df::GREEN, 'a');
	new Block(df::Vector(23, 30), '_', df::GREEN, 'a');
	new Block(df::Vector(24, 30), '_', df::GREEN, 'a');
	new Block(df::Vector(25, 30), '/', df::GREEN, 'a');
	new Block(df::Vector(53, 30), '\\', df::GREEN, 'a');
	new Block(df::Vector(54, 30), '_', df::GREEN, 'a');
	new Block(df::Vector(55, 30), '_', df::GREEN, 'a');
	new Block(df::Vector(56, 30), '_', df::GREEN, 'a');
	new Block(df::Vector(56, 30), '/', df::GREEN, 'a');

	// items
	new Bow(df::Vector(24, 29));
	new Wand(df::Vector(55, 29));

	// bats
	for (int i = 0; i < difficulty * 3 + 2; ++i) {
		new Bat();
	}

	// lever
	new Lever(df::Vector(71, 3));
}

void Map2::stop() {
	// delete all objects
	auto ol = df::ObjectList(WM.getAllObjects());
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		if (oli.currentObject()->getType() != "Player" && oli.currentObject()->getType() != "Map2")
			WM.markForDelete(oli.currentObject());
		oli.next();
	}

	new Map3(difficulty);
	delete this;
}

int Map2::draw() {
	// draw weapon hints
	bool bowOut = false;
	bool wandOut = false;
	auto ol = WM.objectsOfType("Player");
	auto oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()) {
		auto *p_player = dynamic_cast<Player *>(oli.currentObject());
		if (p_player->isHaveBow()) {
			bowOut = true;
			DM.drawString(df::Vector(24, 27),
			              p_player->getPlayerID() == 1 ? "Use Q and E to shoot arrows" : "Use < and > to shoot arrows",
			              df::CENTER_JUSTIFIED, df::WHITE);
		} else if (p_player->isHaveWand()) {
			wandOut = true;
			DM.drawString(df::Vector(55, 27), "Create blocks where you drag", df::CENTER_JUSTIFIED, df::MAGENTA);
		}
		oli.next();
	}

	// draw weapon descriptions
	if (!bowOut) {
		auto bl = WM.objectsOfType("Bow");
		if (!bl.isEmpty()) {
			auto bli = df::ObjectListIterator(&bl);
			DM.drawString(
					df::Vector(bli.currentObject()->getPosition().getX(),
					           bli.currentObject()->getPosition().getY() - 2),
					"Just a normal Bow", df::CENTER_JUSTIFIED, df::WHITE);
		}
	}
	if (!wandOut) {
		auto wl = WM.objectsOfType("Wand");
		if (!wl.isEmpty()) {
			auto wli = df::ObjectListIterator(&wl);
			DM.drawString(
					df::Vector(wli.currentObject()->getPosition().getX(),
					           wli.currentObject()->getPosition().getY() - 2),
					"The Great Wand of Creation", df::CENTER_JUSTIFIED, df::MAGENTA);
		}
	}

	// draw exit hints
	DM.drawString(df::Vector(71, 5), "Pull to leave", df::CENTER_JUSTIFIED, df::YELLOW);

	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(40, 1), "easy", df::CENTER_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(40, 1), "Normal", df::CENTER_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(40, 1), "DIFFICULT", df::CENTER_JUSTIFIED, df::RED);

	return Object::draw();
}
