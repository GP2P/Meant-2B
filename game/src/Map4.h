#ifndef MEANT_2B_DF_MAP4_H
#define MEANT_2B_DF_MAP4_H

#include "ViewObject.h"
#include "Music.h"

class Map4 : public df::ViewObject {

private:

	df::Music *p_music;
	int endingNumber = 0;
	int difficulty = 0;
	int playTime = 0;
	bool goodEnding;

public:

	Map4(int difficulty, int endingNumber);

	Map4(int difficulty, int endingNumber, int playTime);

	~Map4() override;

	int eventHandler(const df::Event *p_e) override;

	int draw() override;
};

#endif //MEANT_2B_DF_MAP4_H
