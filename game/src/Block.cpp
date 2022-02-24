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

int Block::draw() {
	DM.drawCh(getPosition(), '#', df::GREEN);
//	DM.drawCh(getPosition() - df::Vector(0, 0.5), '#', df::GREEN);

	//drawing box for object(debug)
//	float height = getWorldBox(this).getHorizontal();
//	float width = getWorldBox(this).getVertical();
//	df::Vector corner = getWorldBox(this).getCorner();
//	sf::RectangleShape rectangle(sf::Vector2f(width * df::charWidth(), height * df::charHeight()));
//	rectangle.setPosition(df::spacesToPixels(corner).getX(), df::spacesToPixels(corner).getY());
//	rectangle.setFillColor(sf::Color::Red);
//	DM.getWindow()->draw(rectangle);
	return 0;
}
