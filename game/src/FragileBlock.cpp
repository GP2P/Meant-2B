#include "FragileBlock.h"
#include "EventStep.h"
#include "WorldManager.h"

FragileBlock::FragileBlock(df::Vector position, char character, df::Color color, int time) {
	setType("FragileBlock");
	setAltitude(1);
	setPosition(position);
	setCharacter(character);
	setColor(color);
	registerInterest(df::STEP_EVENT);
	timeLeft = time;
}

int FragileBlock::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		timeLeft--;
		if (timeLeft <= 60)
			setColor(df::Color::RED);
		if (timeLeft <= 0)
			WM.markForDelete(this);
		return 1;
	}
	return 0;
}

void buildFragileBlocks(df::Vector start, df::Vector end, char character, df::Color color, int time) {
	for (int x = start.getX(); x <= end.getX(); x++)
		for (int y = start.getY(); y <= end.getY(); y++)
			new FragileBlock(df::Vector(x, y), character, color, time);
}

void buildFragileBlockPlatform(df::Vector start, df::Vector end, char character, df::Color color, int time) {
	for (int x = start.getX(); x <= end.getX(); x++)
		new FragileBlock(df::Vector(x, start.getY()), character, color, time);
}
