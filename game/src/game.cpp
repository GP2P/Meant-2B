#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Box.h"
#include "Map0.h"


int main() {
	// start up game manager
	if (GM.startUp()) {
		LM.writeLog(5, "Error starting game manager!");
		GM.shutDown();
	}

	// Set flush of logfile during development (when done, make false)
	LM.setFlush(true);

	// load resources
	RM.loadMusic("../game/music/02_Stillness_of_Space.ogg", "Map0BGM");
	RM.loadMusic("../game/music/06_Battle_in_Space_Loop.ogg", "Map2BGM");
	RM.loadMusic("../game/music/04_Emergency_No_Alarm.ogg", "Map3BGM");
	RM.loadMusic("../game/music/03_Racing_Through_Asteroids_Loop.ogg", "Map4BGMGood");
	RM.loadMusic("../game/music/05_Building_a_Colony_Loop.ogg", "Map4BGMBad");

	RM.loadSound("../game/SFX/001_Hover_01.wav", "Hover");
	RM.loadSound("../game/SFX/033_Denied_03.wav", "Denied");
	RM.loadSound("../game/SFX/09_Thunder_I.wav", "Thunder");
	RM.loadSound("../game/SFX/08_Charge.wav", "Charge");
	RM.loadSound("../game/SFX/Laser-weapon 8.wav", "Bow");
	RM.loadSound("../game/SFX/Fox_Death.WAV", "Bat");
	RM.loadSound("../game/SFX/Teleport 8.wav", "BossShot");
	RM.loadSound("../game/SFX/Glass Hit.wav", "Crystal");

	RM.loadSprite("../game/sprites/Map0BG.txt", "Map0BG");
	RM.loadSprite("../game/sprites/Map4BGGood.txt", "Map4BGGood");
	RM.loadSprite("../game/sprites/Map4BGBad.txt", "Map4BGBad");

	RM.loadSprite("../game/sprites/Player1-walking.txt", "Player1Walking");
	RM.loadSprite("../game/sprites/Player1-standing.txt", "Player1Standing");
	RM.loadSprite("../game/sprites/Player2-walking.txt", "Player2Walking");
	RM.loadSprite("../game/sprites/Player2-standing.txt", "Player2Standing");

	RM.loadSprite("../game/sprites/ArrowLeft.txt", "ArrowLeft");
	RM.loadSprite("../game/sprites/ArrowRight.txt", "ArrowRight");
	RM.loadSprite("../game/sprites/Bat.txt", "Bat");
	RM.loadSprite("../game/sprites/Boss.txt", "Boss");
	RM.loadSprite("../game/sprites/BossPart.txt", "BossPart");
	RM.loadSprite("../game/sprites/BossPart2.txt", "BossPart2");
	RM.loadSprite("../game/sprites/BossEye.txt", "BossEye");
	RM.loadSprite("../game/sprites/BossProjectile.txt", "BossProjectile");
	RM.loadSprite("../game/sprites/BossCrystal.txt", "BossCrystal");

	// adjust view
	WM.setBoundary(df::Box(df::Vector(), 80, DM.getVertical()));
	WM.setView(df::Box(df::Vector(), 80, DM.getVertical()));

	// start with map 0
	new Map0(0);

	// Run game (this blocks until game loop is over).
	GM.run();

	// Shut everything down.
	GM.shutDown();
}
