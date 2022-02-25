#ifndef MEANT_2B_DF_GATE_H
#define MEANT_2B_DF_GATE_H

#include "Object.h"
#include "Color.h"

enum Direction {
	UNDEFINED_DIRECTION = -1,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Gate : public df::Object {

private:

	Direction direction;
	df::Color color;

public:

	Gate();

	Gate(df::Vector position, Direction new_direction, df::Color new_color);

	int draw();

	int eventHandler(const df::Event *p_e);
};

#endif //MEANT_2B_DF_GATE_H
