#ifndef MEANT_2B_DF_MAP0_H
#define MEANT_2B_DF_MAP0_H

#include "ViewObject.h"
#include "Music.h"

class Map0 : public df::ViewObject {

private:

	df::Music *p_music;
	int difficulty = 0;

public:

	Map0(int difficulty);

	~Map0() override;

	int eventHandler(const df::Event *p_e) override;

	int draw() override;
};

#endif //MEANT_2B_DF_MAP0_H
