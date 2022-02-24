//
// Hero.cpp
//

// Engine includes.
#include <SFML/Graphics/RectangleShape.hpp>
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Bullet.h"
#include "EventNuke.h"
#include "Explosion.h"
#include "GameOver.h"
#include "Hero.h"
#include "DisplayManager.h"

Hero::Hero() {

	// Link to "ship" sprite.
	setSprite("ship");

	// Player controls hero, so register for input events.
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);

	// Need to update rate control each step.
	registerInterest(df::STEP_EVENT);

	// Set object type.
	setType("Hero");

	// Set starting location.
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);

	// Create reticle for firing bullets and aiming.
	p_reticle = new Reticle();
	p_reticle->draw();

	// Set attributes that control actions.
	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 30;
	fire_countdown = fire_slowdown;
	nuke_count = 1;
}

Hero::~Hero() {

	// Create GameOver object.
	new GameOver;

	// Make a big explosion with particles.
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

	// Mark Reticle for deletion.
	WM.markForDelete(p_reticle);
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();

		float height = getWorldBox(this).getHorizontal();
		float width = getWorldBox(this).getVertical();
		df::Vector corner = getWorldBox(this).getCorner();
		sf::RectangleShape rectangle(sf::Vector2f(width * df::charWidth(), height * df::charHeight()));
		rectangle.setPosition(df::spacesToPixels(corner).getX(), df::spacesToPixels(corner).getY());
		rectangle.setFillColor(sf::Color::Red);
		DM.getWindow()->draw(rectangle);

		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse *p_mouse_event) {

	// Pressed button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
	    (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

	switch (p_keyboard_event->getKey()) {
		case df::Keyboard::W:       // up
			if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
				move(-1);
			break;
		case df::Keyboard::S:       // down
			if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
				move(+1);
			break;
		case df::Keyboard::SPACE:   // nuke!
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				nuke();
			break;
		case df::Keyboard::Q:        // quit
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				WM.markForDelete(this);
			break;
		default: // Key not handled.
			return;
	};

	return;
}

// Move up or down.
void Hero::move(int dy) {

	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) &&
	    (new_pos.getY() < WM.getBoundary().getVertical() - 1))
		WM.moveObject(this, new_pos);
}

// Fire bullet towards target.
void Hero::fire(df::Vector target) {

	// See if time to fire.
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet *p = new Bullet(getPosition());
	p->setVelocity(v);

	// Play "fire" sound.
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("fire");
	p_sound->play();
}

// Decrease rate restriction counters.
void Hero::step() {

	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

// Send "nuke" event to all Objects.
void Hero::nuke() {

	// Check if nukes left.
	if (!nuke_count)
		return;
	nuke_count--;

	// Create "nuke" event and send to interested Objects.
	EventNuke nuke;
	WM.onEvent(&nuke);

	// Send "view" event to decrease number of nukes to interested ViewObjects.
	df::EventView ev("Nukes", -1, true);
	WM.onEvent(&ev);

	// Play "nuke" sound.
	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("nuke");
	p_sound->play();
}
