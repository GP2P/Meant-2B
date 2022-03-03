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
	int endingNumber = 0;
	int playTime = 0;

public:

	explicit Map5(int difficulty, df::Music *p_music, int endingNumber, int playTime);

	~Map5() override;

	void start();

	int eventHandler(const df::Event *p_e) override;

	int draw() override;
};

#endif //MEANT_2B_DF_MAP5_H
