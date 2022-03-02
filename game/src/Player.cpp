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
#include "GameManager.h"
#include "Bow.h"
#include "Wand.h"
#include "FragileBlock.h"
#include "Map0.h"
#include "ResourceManager.h"

Player::Player() = default;

Player::Player(int ID) {
	setPlayerID(ID);
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
	mapNum = 0;
	direction = "right";
	hintCD = 60;
	clock = new df::Clock;
	clock->delta();
}

Player::~Player() {
	auto Denied = RM.getSound("Denied");
	Denied->play();

	p_reticle = nullptr;

	// if both players are dead, restart the game
	auto ol = df::ObjectList(WM.objectsOfType("Player"));
	auto oli = df::ObjectListIterator(&ol);
	oli.next();
	if (!oli.isDone()) { // another player alive
		if (mapNum == 2 && isHaveWand())
			new Wand(df::Vector(getPosition().getX(), 29));
		else if (isHaveBow())
			new Bow(df::Vector(getPosition().getX(), 29));
	} else { // both players died
		WM.markForDelete(WM.getAllObjects());
		new Map0(0);
	}
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
			if (playerID == 1)
				setSprite("Player1Standing");
			else
				setSprite("Player2Standing");
			walkingCountdown = -1;
		} else {
			walkingCountdown--;
		}

		if (haveItem() && hintCD > 0) {
			if (getPlayerID() == 1) {
				DM.drawString(getPosition() - df::Vector(0, 3), "Press R to drop item", df::CENTER_JUSTIFIED,
				              df::WHITE);
			}
			if (getPlayerID() == 2) {
				DM.drawString(getPosition() - df::Vector(0, 3), "Press Right Shift to drop item", df::CENTER_JUSTIFIED,
				              df::WHITE);
			}
			hintCD--;
		}
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const auto *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		switch (p_keyboard_event->getKey()) {
			case df::Keyboard::A:    // left
				if (playerID == 1) {
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
				if (playerID == 2) {
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
				if (playerID == 1) {
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
				if (playerID == 2) {
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
				if (playerID == 1)
					jump();
				break;
			case df::Keyboard::UPARROW:    // jump
				if (playerID == 2)
					jump();
				break;
			case df::Keyboard::R:    // place item
				if (playerID == 1) {
					if (haveStone) {
						if (direction == "right") {
							new Stone(getPosition() + df::Vector(1, 1));
						} else {
							new Stone(getPosition() - df::Vector(1, -1));
						}
						setHaveStone(false);
					}
					if (haveBow) {
						if (direction == "right") {
							new Bow(getPosition() + df::Vector(0.5, 1));
						} else {
							new Bow(getPosition() - df::Vector(0.5, -1));
						}
						setHaveBow(false);
					}
					if (haveWand) {
						if (direction == "right") {
							new Wand(getPosition() + df::Vector(0.5, 1));
						} else {
							new Wand(getPosition() - df::Vector(0.5, -1));
						}
						setHaveWand(false);
					}
				}
				break;
			case df::Keyboard::RIGHTSHIFT:    // place item
				if (playerID == 2) {
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
				if (playerID == 1)
					if (haveBow) {
						shoot(getPosition() + df::Vector(1, -0.08));
					}
				break;
			case df::Keyboard::PERIOD:    // shoot arrow to right
				if (playerID == 2)
					if (haveBow) {
						shoot(getPosition() + df::Vector(1, -0.08));
					}
				break;
			case df::Keyboard::Q:    // shoot arrow to left
				if (playerID == 1)
					if (haveBow) {
						shoot(getPosition() - df::Vector(1, 0.08));
					}
				break;
			case df::Keyboard::COMMA:    // shoot arrow to left
				if (playerID == 2)
					if (haveBow) {
						shoot(getPosition() - df::Vector(1, 0.08));
					}
				break;
			case df::Keyboard::Z:    // replay game
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
					WM.markForDelete(WM.getAllObjects());
					new Map0(0);
				}
				break;
			case df::Keyboard::X:    // kill game
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
					GM.setGameOver(true);
				}
				break;
			default:    // Key not included
				break;
		}
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const auto *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
		if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
			if (mapNum == 3 && haveBow)
				shoot(p_mouse_event->getMousePosition());
		if (p_mouse_event->getMouseAction() == df::PRESSED && p_mouse_event->getMouseButton() == df::Mouse::LEFT)
			if ((mapNum == 2 || mapNum == 4) && haveWand) {
				new FragileBlock(df::Vector((int) p_mouse_event->getMousePosition().getX(),
				                            (int) p_mouse_event->getMousePosition().getY()), '@', df::YELLOW, 150);
				return 1;
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
	v = df::Vector(v.getX(), v.getY() / 2);


	auto *p = new Arrow(getPosition());
	if ((target - getPosition()).getX() < 0) {
		p->setSprite("ArrowLeft");
	} else {
		p->setSprite("ArrowRight");
	}
	p->setVelocity(v);
}

int Player::getPlayerID() const {
	return playerID;
}

void Player::setPlayerID(int id) {
	playerID = id;
}

bool Player::haveItem() {
	return (haveStone || haveBow || haveWand);
}

int Player::draw() {
	bool result = Object::draw();

	if (haveStone) {
		if (direction == "right") {
			DM.drawCh(getPosition() + df::Vector(1, 0), '@', df::WHITE);
		} else {
			DM.drawCh(getPosition() - df::Vector(1, 0), '@', df::WHITE);
		}
	}
	if (haveBow) {
		if (direction == "right") {
			DM.drawCh(getPosition() + df::Vector(1, 0), '|', df::WHITE);
			DM.drawCh(getPosition() + df::Vector(1.6, 0), ')', df::YELLOW);
		} else {
			DM.drawCh(getPosition() - df::Vector(1, 0), '|', df::WHITE);
			DM.drawCh(getPosition() - df::Vector(1.6, 0), '(', df::YELLOW);
		}
	}
	if (haveWand) {
		if (direction == "right") {
			DM.drawCh(getPosition() + df::Vector(1.3, 0), '/', df::WHITE);
			DM.drawCh(getPosition() + df::Vector(1.8, -0.5), '*', df::MAGENTA);
		} else {
			DM.drawCh(getPosition() - df::Vector(1.3, 0), '\\', df::WHITE);
			DM.drawCh(getPosition() - df::Vector(1.8, +0.5), '*', df::MAGENTA);
		}
	}

	// draw time
	int time = static_cast<int>(clock->split() / 1000000);
	std::string s = std::to_string(time);
	DM.drawString(df::Vector(5, 1), "Total Time:" + s, df::LEFT_JUSTIFIED, df::WHITE);

	return result;
}

df::Clock *Player::getClock() const {
	return clock;
}

void Player::setClock(df::Clock *clock) {
	Player::clock = clock;
}

long Player::getTotalTime() const {
	return totalTime;
}

void Player::setTotalTime(long totalTime) {
	Player::totalTime = totalTime;
}
