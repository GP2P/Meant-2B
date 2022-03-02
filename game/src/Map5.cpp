#include "Map5.h"
#include "WorldManager.h"
#include "Map0.h"
#include "DisplayManager.h"

Map5::Map5(int difficulty, df::Music *p_music) {
	this->difficulty = difficulty;
	this->p_music = p_music;
}

Map5::~Map5() {

}

void Map5::start() {

}

void Map5::stop() {
	WM.markForDelete(WM.getAllObjects());
	new Map0(difficulty);
}

int Map5::draw() {
	// show current difficulty
	if (difficulty == 0)
		DM.drawString(df::Vector(40, 1), "easy", df::CENTER_JUSTIFIED, df::WHITE);
	else if (difficulty == 1)
		DM.drawString(df::Vector(40, 1), "Normal", df::CENTER_JUSTIFIED, df::YELLOW);
	else if (difficulty == 2)
		DM.drawString(df::Vector(40, 1), "DIFFICULT", df::CENTER_JUSTIFIED, df::RED);

	return Object::draw();
}
