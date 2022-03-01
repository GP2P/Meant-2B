#include "Gate.h"
#include "DisplayManager.h"
#include "EventGate.h"
#include "Vector.h"
#include "LogManager.h"

Gate::Gate() {
}

Gate::Gate(df::Vector position, Direction new_direction, df::Color new_color) {
	setPosition(position);
	direction = new_direction;
	color = new_color;
	registerInterest("GateEvent");
	open = false;
	switch (direction) {
		case UP:
			setBox(df::Box(df::Vector(-0.5, -5.5), 1, 5));
			break;
		case DOWN:
			setBox(df::Box(df::Vector(-0.5, -0.5), 1, 5));
			break;
		default:
			break;
	}
}

int Gate::draw() {
	switch (direction) {

		case UP:
			for (int i = 0; i < 5; i++) {
				DM.drawCh(getPosition() + df::Vector(0, -i), '|', color);
			}
			return 0;
		case DOWN:
			for (int i = 0; i < 5; i++) {
				DM.drawCh(getPosition() + df::Vector(0, i), '|', color);
			}
			return 0;
		default:
			return -1;
	}
}

int Gate::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == "GateEvent") {
		const auto *p_oge = dynamic_cast <const EventGate *> (p_e);
		if (p_oge->getColor() == color) {
			if (p_oge->getOpen() && !open) {
				LM.writeLog("open gate");
				open = true;
				setPosition(getPosition() - df::Vector(0, 5));
			} else if (!p_oge->getOpen() && open) {
				LM.writeLog("close gate");
				open = false;
				setPosition(getPosition() + df::Vector(0, 5));
			}
		}
		return 1;
	}
	return 0;
}
