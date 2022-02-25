#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Box.h"
#include "Map1.h"

int main() {
	// start up game manager
	if (GM.startUp()) {
		LM.writeLog(5, "Error starting game manager!");
		GM.shutDown();
	}

	// Set flush of logfile during development (when done, make false)
	LM.setFlush(true);

	// load resources
	RM.loadSprite("../game/sprites/Map1BG.txt", "Map1BG");
	RM.loadSprite("../game/sprites/Player.txt", "Player");
	RM.loadSprite("../game/sprites/Arrow.txt", "Arrow");
	RM.loadMusic("../game/music/Map1BGM.wav", "Map1BGM");

	// adjust view
	WM.setBoundary(df::Box(df::Vector(), 80, DM.getVertical()));
	WM.setView(df::Box(df::Vector(), 80, DM.getVertical()));

	// Create GameStart object.
	new Map1();

	// Run game (this blocks until game loop is over).
	GM.run();

	// Shut everything down.
	GM.shutDown();
}
