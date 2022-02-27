#include "PressurePlate.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventGate.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"

PressurePlate::PressurePlate() {
	setType("PressurePlate");
	setSolidness(df::SOFT);
	setAltitude(1);
	color = df::COLOR_DEFAULT;
	maxopencountdown = 10;
	opencountdown = 0;
	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
	setBox(df::Box(df::Vector(-1, -1), 3, 1));
}

PressurePlate::PressurePlate(df::Vector position, df::Color new_color, int opcountdown) {
	setType("PressurePlate");
	setSolidness(df::SOFT);
	setAltitude(1);
	setPosition(position);
	color = new_color;
	maxopencountdown = opcountdown;
	opencountdown = 0;
	registerInterest(df::STEP_EVENT);
}

int PressurePlate::draw() {
	if (opencountdown <= 0) {
		DM.drawCh(getPosition() + df::Vector(-1, 0.15), '_', color);
		DM.drawCh(getPosition() + df::Vector(0, 0.15), '_', color);
		DM.drawCh(getPosition() + df::Vector(1, 0.15), '_', color);
	} else {
		DM.drawCh(getPosition() + df::Vector(-1, 0.3), '_', color);
		DM.drawCh(getPosition() + df::Vector(0, 0.3), '_', color);
		DM.drawCh(getPosition() + df::Vector(1, 0.3), '_', color);
	}

	return 0;
}

int PressurePlate::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_ce = dynamic_cast <const df::EventCollision *> (p_e);
		if ((p_ce->getObject1()->getType() == "Player") ||
		    (p_ce->getObject2()->getType() == "Player")) {
			EventGate *ev = new EventGate;
			ev->setColor(color);
			ev->setOpen(true);
			WM.onEvent(ev);
			opencountdown = maxopencountdown;
			return 1;
		}
		if ((p_ce->getObject1()->getType() == "Stone") ||
		    (p_ce->getObject2()->getType() == "Stone")) {
			EventGate *ev = new EventGate;
			ev->setColor(color);
			ev->setOpen(true);
			WM.onEvent(ev);
			opencountdown = maxopencountdown;
			return 1;
		}
	}
	if (p_e->getType() == df::STEP_EVENT) {
		if (opencountdown == 0) {
			EventGate *eog = new EventGate;
			eog->setColor(color);
			eog->setOpen(false);
			WM.onEvent(eog);
			opencountdown = -1;
			return 1;
		} else if (opencountdown > 0) {
			opencountdown--;
			return 1;
		}

	}
	return 0;
}
