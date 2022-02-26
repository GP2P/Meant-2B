#include "Lever.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventGate.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "Player.h"
#include "EventKeyboard.h"

Lever::Lever() {
	setType("Lever");
	setSolidness(df::SOFT);
	setAltitude(1);
}

Lever::Lever(df::Vector position) {
	setType("Lever");
	setSolidness(df::SOFT);
	setAltitude(1);
	setPosition(position);
    nearCountdown = 0;
    nearPlayer = false;
    player = NULL;
	color = df::YELLOW;
	character = '/';
    setAltitude(3);
    registerInterest(df::STEP_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::COLLISION_EVENT);

}

int Lever::draw() {
	DM.drawCh(getPosition() - df::Vector(0, 0.1), character, color);

    if (nearPlayer) {
        if (player->getID() == 1) {
            DM.drawString(getPosition() - df::Vector(0, 4), "Press E to pull lever", df::CENTER_JUSTIFIED, df::WHITE);
        }
        if (player->getID() == 2) {
            DM.drawString(getPosition() - df::Vector(0, 4), "Press slash to pull lever", df::CENTER_JUSTIFIED, df::WHITE);
        }
    }
    return 1;
}

int Lever::eventHandler(const df::Event *p_e) {

    if (p_e->getType() == df::COLLISION_EVENT) {
        const auto *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
        if ((p_ce->getObject1()->getType() == "Player")) {
            auto *p = dynamic_cast <Player *> (p_ce->getObject1());
            nearPlayer = true;
            player = p;
            nearCountdown = 4;
            return 1;
        } else if (p_ce->getObject2()->getType() == "Player") {
            auto *p = dynamic_cast <Player *> (p_ce->getObject2());
            nearPlayer = true;
            player = p;
            nearCountdown = 4;
            return 1;
        }
    }
    if (p_e->getType() == df::STEP_EVENT) {
        nearCountdown--;
        if (nearCountdown <= 0) {
            nearPlayer = false;
            player = nullptr;
        }
        return 1;
    }

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
        switch (p_keyboard_event->getKey()) {
            case df::Keyboard::E:
                if (nearPlayer && player->getID() == 1) {
                    character = '\\';
                }
                break;
            case df::Keyboard::SLASH:
                if (nearPlayer && player->getID() == 2) {
                    character = '\\';
                }
                break;
            default:    // Key not included
                break;
        }
        return 1;
    }
}
