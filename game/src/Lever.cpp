#include "Lever.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventOpenGate.h"
#include "WorldManager.h"
#include "LogManager.h"



Lever::Lever(){
    setType("Lever");
    setSolidness(df::SOFT);
    setAltitude(1);
}

Lever::Lever(df::Vector position, df::Color new_color){
    setType("Lever");
    setSolidness(df::SOFT);
    setAltitude(1);
    setPosition(position);
    color = new_color;
    character = '/';
}

int Lever::draw() {
    DM.drawCh(getPosition()-df::Vector(0,0.1), character, color);
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

int Lever::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
        if ((p_ce -> getObject1() -> getType() == "Player") ||
            (p_ce -> getObject2() -> getType() == "Player")) {
            EventOpenGate *ev = new EventOpenGate;
            ev->setColor(color);
            ev->setOpen(true);
            WM.onEvent(ev);
            character = '\\';
            return 1;
        }
        return 0;
    }
}