#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Box.h"
#include "Map0.h"
#include "Boss.h"

int main() {
	// start up game manager
	if (GM.startUp()) {
		LM.writeLog(5, "Error starting game manager!");
		GM.shutDown();
	}

	// Set flush of logfile during development (when done, make false)
	LM.setFlush(true);

	// load resources
	RM.loadSprite("../game/sprites/Click2Start.txt", "Click2Start");
	RM.loadMusic("../game/music/Map0BGM.wav", "Map0BGM");
	RM.loadSprite("../game/sprites/Map1BG.txt", "Map1BG");
	RM.loadMusic("../game/music/Map1BGM.wav", "Map1BGM");
	RM.loadSprite("../game/sprites/Map2BG.txt", "Map2BG");
	RM.loadMusic("../game/music/Map2BGM.wav", "Map2BGM");
	RM.loadSprite("../game/sprites/Map3BG.txt", "Map3BG");
	RM.loadMusic("../game/music/Map3BGM.wav", "Map3BGM");

	RM.loadSprite("../game/sprites/Player1-walking.txt", "Player1Walking");
	RM.loadSprite("../game/sprites/Player1-standing.txt", "Player1Standing");
	RM.loadSprite("../game/sprites/Player2-walking.txt", "Player2Walking");
	RM.loadSprite("../game/sprites/Player2-standing.txt", "Player2Standing");

	RM.loadSprite("../game/sprites/ArrowLeft.txt", "ArrowLeft");
    RM.loadSprite("../game/sprites/ArrowRight.txt", "ArrowRight");
    RM.loadSprite("../game/sprites/Bat.txt", "Bat");
    RM.loadSprite("../game/sprites/Boss.txt", "Boss");

	// adjust view
	WM.setBoundary(df::Box(df::Vector(), 80, DM.getVertical()));
	WM.setView(df::Box(df::Vector(), 80, DM.getVertical()));

	// start with map 0
    new Map0();

	// Run game (this blocks until game loop is over).
	GM.run();

	// Shut everything down.
	GM.shutDown();
}
