//
// Created by 方申 on 2/25/22.
//

#include "Bat.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "WorldManager.h"

Bat::Bat() {
    setType("Bat");
    setSprite("Bat");
    int x = rand() % (DM.getHorizontal() - 10) + 5;
    int y = rand() % (DM.getVertical()-10) +5;
    df::Vector position(x,y);
    setPosition(position);
    moveCountdown = 30;
    registerInterest(df::STEP_EVENT);
    registerInterest(df::COLLISION_EVENT);

    setSolidness(df::SOFT);
}

int Bat::eventHandler(const df::Event *p_e) {

    if (p_e->getType() == df::STEP_EVENT) {
        if(moveCountdown > 0 && (getPosition().getX() < DM.getHorizontal()-2) && (getPosition().getX() > 2)
                                                                                         && (getPosition().getY() < DM.getVertical()-7) && (getPosition().getY() > 1)){
            moveCountdown--;
        } else{
            int x = rand() % (DM.getHorizontal() - 10) + 5;
            int y = rand() % (DM.getVertical()-10) +5;
            df::Vector direction(x,y);
            direction = (direction - getPosition());
            direction.normalize();
            direction.scale(0.5);
            setVelocity(direction);
            moveCountdown = 30;
        }
        return 1;
    }

    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
        if ((p_ce->getObject1()->getType() == "Player") ||
            (p_ce->getObject2()->getType() == "Player")) {
            WM.markForDelete(p_ce->getObject1());
            WM.markForDelete(p_ce->getObject2());
        }
    }
}