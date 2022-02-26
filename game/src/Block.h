#ifndef DF_BLOCK_H
#define DF_BLOCK_H

#include "Object.h"

class Block : public df::Object {

private:

	char character = '#';
	df::Color color = df::GREEN;

public:

	Block();

	Block(df::Vector position);

	Block(df::Vector position, char character);

	Block(df::Vector position, char character, df::Color color);

	Block(df::Vector position, char character, df::Color color, char type);

	char getCharacter() const;

	void setCharacter(char character);

	df::Color getColor() const;

	void setColor(df::Color color);

	int draw();
};

// limited to build only on integer coordinates, will convert floats to ints
void buildBlocks(df::Vector start, df::Vector end, char character = '#', df::Color color = df::GREEN);

#endif //DF_BLOCK_H
