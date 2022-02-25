#ifndef MEANT_2B_DF_MAP0_H
#define MEANT_2B_DF_MAP0_H

#include "ViewObject.h"
#include "Music.h"

class Map0 : public df::ViewObject {

private:
	df::Music *p_music;

public:
	Map0();

	~Map0();

	void start();

	int eventHandler(const df::Event *p_e);

	int draw();
};

#endif //MEANT_2B_DF_MAP0_H
