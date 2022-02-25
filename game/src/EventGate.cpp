#include "EventGate.h"

EventGate::EventGate() {
	setType("GateEvent");
}

df::Color EventGate::getColor() const {
	return color;
}

void EventGate::setColor(df::Color Color) {
	color = Color;
}

bool EventGate::getOpen() const {
	return open;
}

void EventGate::setOpen(bool new_open) {
	open = new_open;
}
