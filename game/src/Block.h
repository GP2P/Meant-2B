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

	char getCharacter() const;

	void setCharacter(char character);

	df::Color getColor() const;

	void setColor(df::Color color);

	int draw();
};

#endif //DF_BLOCK_H
