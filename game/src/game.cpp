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
	RM.loadSprite("../game/sprites/Map1BG.txt", "Map1BG");
	RM.loadMusic("../game/music/Map1BGM.wav", "Map1BGM");

	RM.loadSprite("../game/sprites/Player1-walking.txt", "Player1Walking");
	RM.loadSprite("../game/sprites/Player1-standing.txt", "Player1Standing");
	RM.loadSprite("../game/sprites/Player2-walking.txt", "Player2Walking");
	RM.loadSprite("../game/sprites/Player2-standing.txt", "Player2Standing");
	RM.loadSprite("../game/sprites/Arrow.txt", "Arrow");
    RM.loadSprite("../game/sprites/Boss.txt", "Boss");

	// adjust view
	WM.setBoundary(df::Box(df::Vector(), 80, DM.getVertical()));
	WM.setView(df::Box(df::Vector(), 80, DM.getVertical()));

	// Create GameStart object.
	new Boss();

	// Run game (this blocks until game loop is over).
	GM.run();

	// Shut everything down.
	GM.shutDown();
}
