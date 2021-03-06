#include "Reticle.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "DisplayManager.h"

Reticle::Reticle(df::Color color) {
	this->color = color;
	setType("Reticle");
	setSolidness(df::SPECTRAL);
	setAltitude(4); // Make Reticle in foreground.

	// Reticle moves with mouse, so register.
	registerInterest(df::MSE_EVENT);

	// Start reticle in center of window.
	df::Vector p(WM.getBoundary().getHorizontal() / 2,
	             WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Reticle::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::MSE_EVENT) {
		const auto *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// Change location to new mouse position.
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}

	// If get here, have ignored this event.
	return 0;
}

// Draw reticle on window.
int Reticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, color);
}
