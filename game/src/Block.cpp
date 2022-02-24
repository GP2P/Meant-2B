#include "Block.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "utility.h"

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
