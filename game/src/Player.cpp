#include "Player.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"

Player::Player() {
	setType("Player");
	setSolidness(df::HARD);
	setSprite("Player");
	setVelocity(df::Vector(1, 0));
	registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	acceleration = df::Vector(0, 0.01);
	jumpspeed = 0.3;
	allowdoublejump = true;
	jumpCount = 0;
}

bool Player::onGround() {
	return !WM.getCollisions(this, getPosition() + getVelocity()).isEmpty();
}

int Player::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		if (!onGround()) setVelocity(getVelocity() + acceleration);
		else setVelocity(df::Vector(0, 0));
		return 1;
	} else if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		switch (p_keyboard_event->getKey()) {
			case df::Keyboard::A:    // left
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
					move(-1);
				break;
			case df::Keyboard::D:    // right
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
					move(+1);
				break;
			case df::Keyboard::W:    // jump
				jump();
				break;
			case df::Keyboard::E:    // grab item
				break;
			default:    // Key not included
				break;
		};
		return 1;
	}
	return 0;
}

int Player::move(int distance) {

	//getting new position of movement
	df::Vector new_pos(getPosition().getX() + distance, getPosition().getY());

	//move object
	return WM.moveObject(this, new_pos);
}

int Player::jump() {
	if (onGround()) {
		setVelocity(df::Vector(0, -jumpspeed));
		jumpCount = 1;
		return 1;
	}

	if (allowdoublejump && (jumpCount == 1)) {
		setVelocity(df::Vector(0, -jumpspeed));
		jumpCount = 0;
		return 2;
	}
	return 0;
}