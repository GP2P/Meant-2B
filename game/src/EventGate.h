#ifndef MEANT_2B_DF_EVENTGATE_H
#define MEANT_2B_DF_EVENTGATE_H

#include "Event.h"
#include "Color.h"

class EventGate : public df::Event {
private:
	df::Color color; //only trigger with same color can open gate
	bool open; // open(true) or close (false)

public:
	EventGate();

	df::Color getColor() const;

	void setColor(df::Color Color);

	bool getOpen() const;

	void setOpen(bool open);
};

#endif //MEANT_2B_DF_EVENTGATE_H
