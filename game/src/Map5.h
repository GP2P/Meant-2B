#ifndef MEANT_2B_DF_MAP5_H
#define MEANT_2B_DF_MAP5_H

#include "ViewObject.h"
#include "Music.h"

class Map5 : public df::ViewObject {

private:

	df::Music *p_music;
	int difficulty = 0;
	int time;
    float scoreListEasy[3];
    float scoreListNormal[3];
    float scoreListDifficult[3];


public:

	explicit Map5(int difficulty, df::Music *p_music);

	~Map5() override;

	void start();

	void stop();

	int draw() override;
};

#endif //MEANT_2B_DF_MAP5_H
