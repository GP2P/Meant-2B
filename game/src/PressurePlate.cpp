//
// Created by 方申 on 2/23/22.
//

#include "PressurePlate.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventOpenGate.h"
#include "WorldManager.h"
#include "LogManager.h"



PressurePlate::PressurePlate(){
    setType("PressurePlate");
    setSolidness(df::SOFT);
    setAltitude(1);
}

PressurePlate::PressurePlate(df::Vector position, df::Color new_color){
    setType("PressurePlate");
    setSolidness(df::SOFT);
    setAltitude(1);
    setPosition(position);
    color = new_color;
}

int PressurePlate::draw() {
    DM.drawCh(getPosition()-df::Vector(0,0.1), '_', color);
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

int PressurePlate::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
        if ((p_ce -> getObject1() -> getType() == "Player") ||
            (p_ce -> getObject2() -> getType() == "Player")) {
            EventOpenGate *ev = new EventOpenGate;
            ev->setColor(color);
            WM.onEvent(ev);
        }
    }
}