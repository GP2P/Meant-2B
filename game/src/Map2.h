#ifndef MEANT_2B_DF_MAP2_H
#define MEANT_2B_DF_MAP2_H

#include "ViewObject.h"
#include "Music.h"
#include "Vector.h"

class Map2 : public df::ViewObject {

private:

	df::Music *p_music;

public:

	Map2();

	~Map2() override;

	void start();

	void stop();

	int draw() override;
};

#endif //MEANT_2B_DF_MAP2_H
