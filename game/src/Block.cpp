#include "Block.h"
#include "DisplayManager.h"
#include "Vector.h"

Block::Block() {
	setType("Block");
	setAltitude(1);
}

Block::Block(df::Vector position) {
	setType("Block");
	setAltitude(1);
	setPosition(position);
}

Block::Block(df::Vector position, char character) {
	setType("Block");
	setAltitude(1);
	setPosition(position);
	setCharacter(character);
}

Block::Block(df::Vector position, char character, df::Color color) {
	setType("Block");
	setAltitude(1);
	setPosition(position);
	setCharacter(character);
	setColor(color);
}

Block::Block(df::Vector position, char character, df::Color color, char type) {
	if (type == 'c')
		setType("Cage");
	else if (type == 'a') {
		setType("Altar");
		setSolidness(df::Solidness::SOFT);
	} else
		setType("Block");
	setAltitude(1);
	setPosition(position);
	setCharacter(character);
	setColor(color);
}

int Block::draw() {
	return DM.drawCh(getPosition(), character, color);
}

char Block::getCharacter() const {
	return character;
}

void Block::setCharacter(char character) {
	Block::character = character;
}

df::Color Block::getColor() const {
	return color;
}

void Block::setColor(df::Color color) {
	Block::color = color;
}

void buildBlocks(df::Vector start, df::Vector end, char character, df::Color color) {
	for (int x = start.getX(); x <= end.getX(); x++)
		for (int y = start.getY(); y <= end.getY(); y++)
			new Block(df::Vector(x, y), character, color);
}
