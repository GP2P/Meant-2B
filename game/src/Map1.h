#ifndef DF_MAP1_H
#define DF_MAP1_H

#include "ViewObject.h"
#include "Music.h"

class Map1 : public df::ViewObject {

private:

	df::Music *p_music;
	int difficulty = 0;

public:

	explicit Map1(int difficulty, df::Music *p_music);

	~Map1() override;

	void start();

	void stop();

	int draw() override;
};

#endif //DF_MAP1_H
