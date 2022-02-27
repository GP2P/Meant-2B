#ifndef MEANT_2B_DF_MAP4_H
#define MEANT_2B_DF_MAP4_H

#include "ViewObject.h"
#include "Music.h"

class Map4 : public df::ViewObject {

private:

	df::Music *p_music;
	int countDown = 10;
	int endingNumber = 0;

public:

	Map4();

	Map4(int endingNumber);

	~Map4() override;

	int eventHandler(const df::Event *p_e) override;

	int draw() override;
};

#endif //MEANT_2B_DF_MAP4_H
