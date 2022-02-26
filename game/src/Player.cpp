#include "Player.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "Arrow.h"
#include "EventMouse.h"
#include "Stone.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Map1.h"
#include "LogManager.h"
#include "GameManager.h"
#include "Bow.h"
#include "Wand.h"

Player::Player() = default;

Player::Player(int ID) {
	setID(ID);
	setType("Player");
	setSolidness(df::HARD);
	if (ID == 1)
		setSprite("Player1Standing");
	else
		setSprite("Player2Standing");
	setVelocity(df::Vector());
	registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);
	acceleration = df::Vector(0, 0.1);
	jumpSpeed = 0.95;
	shootSlowdown = 30;
	shootCountdown = shootSlowdown;
	walkingCountdown = 0;
	haveStone = false;
	inMap = true;
    direction = "right";
    hintcd = 60;
}

Player::~Player() {
// if both players are dead, end the game
	auto ol = df::ObjectList(WM.objectsOfType("Player"));
	auto oli = df::ObjectListIterator(&ol);
	oli.next();
	if (oli.isDone())
		GM.setGameOver();
}

bool Player::onGround() {
	df::ObjectList collisions = WM.getCollisions(this, getPosition() + getVelocity());

	// soft collisions don't count as on ground
	if (!collisions.isEmpty()) {
		auto oli = df::ObjectListIterator(&collisions);
		while (!oli.isDone()) {
			if (oli.currentObject()->getSolidness() == df::HARD)
				return true;
			oli.next();
		}
		return false;
	} else return false;
}

int Player::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		if (!onGround()) setVelocity(getVelocity() + acceleration);
		else setVelocity(df::Vector(0, 0));

		shootCountdown--;
		if (shootCountdown < 0)
			shootCountdown = 0;

		if (walkingCountdown == 0) {
			if (ID == 1)
				setSprite("Player1Standing");
			else
				setSprite("Player2Standing");
			walkingCountdown = -1;
		} else {
			walkingCountdown--;
		}
		if (haveItem() && hintcd>0) {
			if (getID() == 1) {
				DM.drawString(getPosition() - df::Vector(0, 3), "Press R to drop item", df::CENTER_JUSTIFIED,
				              df::WHITE);
			}
			if (getID() == 2) {
				DM.drawString(getPosition() - df::Vector(0, 3), "Press Right Shift to drop item", df::CENTER_JUSTIFIED,
				              df::WHITE);
			}
            hintcd --;
		}
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		switch (p_keyboard_event->getKey()) {
            case df::Keyboard::A:    // left
                if (ID == 1) {
                    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                        if (walkingCountdown < 1 && onGround()) {
                            setSprite("Player1Walking");
                            walkingCountdown = 10;
                            direction = "left";
                        }
                    WM.moveObject(this, df::Vector(getPosition().getX() - (float) 1.0, getPosition().getY()));
                }
                break;
            case df::Keyboard::LEFTARROW:    // left
                if (ID == 2) {
                    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                        if (walkingCountdown < 1 && onGround()) {
                            setSprite("Player2Walking");
                            walkingCountdown = 10;
                            direction = "left";
                        }
                    WM.moveObject(this, df::Vector(getPosition().getX() - (float) 1.0, getPosition().getY()));
                }
                break;
            case df::Keyboard::D:    // right
                if (ID == 1) {
                    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                        if (walkingCountdown < 1 && onGround()) {
                            setSprite("Player1Walking");
                            walkingCountdown = 10;
                            direction = "right";
                        }
                    WM.moveObject(this, df::Vector(getPosition().getX() + (float) 1.0, getPosition().getY()));
                }
                break;
            case df::Keyboard::RIGHTARROW:    // right
                if (ID == 2) {
                    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                        if (walkingCountdown < 1 && onGround()) {
                            setSprite("Player2Walking");
                            walkingCountdown = 10;
                            direction = "right";
                        }
                    WM.moveObject(this, df::Vector(getPosition().getX() + (float) 1.0, getPosition().getY()));
                }
                break;
            case df::Keyboard::W:    // jump
                if (ID == 1)
                    jump();
                break;
            case df::Keyboard::UPARROW:    // jump
                if (ID == 2)
                    jump();
                break;
            case df::Keyboard::R:    // place item
                if (ID == 1) {
                    if (haveStone) {
                        if (direction == "right") {
                            new Stone(getPosition() + df::Vector(1, 1));
                        } else {
                            new Stone(getPosition() - df::Vector(1, -1));
                        }
                        haveStone = false;
                    }
                    if (haveBow) {
                        if (direction == "right") {
                            new Bow(getPosition() + df::Vector(0.5, 1));
                        } else {
                            new Bow(getPosition() - df::Vector(0.5, -1));
                        }
                        haveBow = false;
                    }
                    if (haveWand) {
                        if (direction == "right") {
                            new Wand(getPosition() + df::Vector(0.5, 1));
                        } else {
                            new Wand(getPosition() - df::Vector(0.5, -1));
                        }
                        haveWand = false;
                    }
                }
				break;
			case df::Keyboard::RIGHTSHIFT:    // place item
				if (ID == 2){
                    if (haveStone) {
                        if (direction == "right") {
                            new Stone(getPosition() + df::Vector(1, 1));
                        } else {
                            new Stone(getPosition() - df::Vector(1, -1));
                        }
                        haveStone = false;
                    }
                    if (haveBow) {
                        if (direction == "right") {
                            new Bow(getPosition() + df::Vector(0.5, 1));
                        } else {
                            new Bow(getPosition() - df::Vector(0.5, -1));
                        }
                        haveBow = false;
                    }
                    if (haveWand) {
                        if (direction == "right") {
                            new Wand(getPosition() + df::Vector(0.5, 1));
                        } else {
                            new Wand(getPosition() - df::Vector(0.5, -1));
                        }
                        haveWand = false;
                    }
                }
				break;
            case df::Keyboard::E:    // shoot arrow to right
                if (ID == 1)
                    if (haveBow) {
                        shoot(getPosition()+df::Vector(1,-0.08));
                    }
                break;
            case df::Keyboard::PERIOD:    // shoot arrow to right
                if (ID == 2)
                    if (haveBow) {
                        shoot(getPosition()+df::Vector(1,-0.08));
                    }
                break;
            case df::Keyboard::Q:    // shoot arrow to left
                if (ID == 1)
                    if (haveBow) {
                        shoot(getPosition()-df::Vector(1,0.08));
                    }
                break;
            case df::Keyboard::COMMA:    // shoot arrow to left
                if (ID == 2)
                    if (haveBow) {
                        shoot(getPosition()-df::Vector(1,0.08));
                    }
                break;
			default:    // Key not included
				break;
		}
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const auto *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
		if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		    (p_mouse_event->getMouseButton() == df::Mouse::LEFT) && haveBow) {
			shoot(p_mouse_event->getMousePosition());
		}
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT) {
		inMap = false;
		auto ol = df::ObjectList(WM.objectsOfType("Player"));
		auto oli = df::ObjectListIterator(&ol);
		while (!oli.isDone()) {
			auto *p_player = dynamic_cast<Player *>(oli.currentObject());
			if (p_player->isInMap())
				return 1;
			oli.next();
		}
		auto ml = df::ObjectList(WM.objectsOfType("Map1"));
		auto mli = df::ObjectListIterator(&ml);
		auto *p_Map1 = dynamic_cast<Map1 *>(mli.currentObject());
		p_Map1->stop();
	}
	return 0;
}

int Player::jump() {
	if (onGround()) {
		setVelocity(df::Vector(0, -jumpSpeed));
		return 1;
	}

	return 0;
}

void Player::shoot(df::Vector target) {

	// See if time to shoot.
	if (shootCountdown > 0)
		return;
	shootCountdown = shootSlowdown;

	// Shoot Arrow towards target.
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1.5);

	auto *p = new Arrow(getPosition());
    if((target - getPosition()).getX()<0){
        p->setSprite("ArrowLeft");
    } else{
        p->setSprite("ArrowRight");
    }
	p->setVelocity(v);
}

int Player::getID() const {
	return ID;
}

void Player::setID(int id) {
	ID = id;
}

bool Player::haveItem() {
	return (haveStone || haveBow || haveWand);
}

int Player::draw() {
    Object::draw();

    if(haveStone){
        if(direction == "right") {
            DM.drawCh(getPosition()+df::Vector(1,0), '@', df::WHITE);
        } else{
            DM.drawCh(getPosition()-df::Vector(1,0), '@', df::WHITE);
        }
    }
    if(haveBow){
        if(direction == "right") {
            DM.drawCh(getPosition() + df::Vector(1,0), '|', df::WHITE);
            DM.drawCh(getPosition()+ df::Vector(1.6,0), ')', df::YELLOW);
        } else{
            DM.drawCh(getPosition() - df::Vector(1,0), '|', df::WHITE);
            DM.drawCh(getPosition()- df::Vector(1.6,0), '(', df::YELLOW);
        }
    }
    if(haveWand){
        if(direction == "right") {
            DM.drawCh(getPosition() + df::Vector(1.3, 0), '/', df::WHITE);
            DM.drawCh(getPosition() + df::Vector(1.8, -0.5), '*', df::MAGENTA);
        } else{
            DM.drawCh(getPosition() - df::Vector(1.3, 0), '\\', df::WHITE);
            DM.drawCh(getPosition() - df::Vector(1.8, +0.5), '*', df::MAGENTA);
        }
    }
}
