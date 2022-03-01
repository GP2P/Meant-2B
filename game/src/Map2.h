#ifndef MEANT_2B_DF_MAP2_H
#define MEANT_2B_DF_MAP2_H

#include "ViewObject.h"
#include "Music.h"
#include "Vector.h"

class Map2 : public df::ViewObject {

private:

	df::Music *p_music;
	int difficulty = 0;

public:

	explicit Map2(int difficulty);

	~Map2() override;

	void start();

	void stop();

	int draw() override;
};

#endif //MEANT_2B_DF_MAP2_H
