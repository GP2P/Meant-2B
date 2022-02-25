#ifndef MEANT_2B_DF_LEVER_H
#define MEANT_2B_DF_LEVER_H

#include "Object.h"
#include "Color.h"

class Lever : public df::Object {

private:

	df::Color color;

	char character;

public:

	Lever();

	Lever(df::Vector position, df::Color new_color);

	int draw();

	int eventHandler(const df::Event *p_e);

};

#endif //MEANT_2B_DF_LEVER_H
