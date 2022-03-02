#ifndef MEANT_2B_DF_MAP3_H
#define MEANT_2B_DF_MAP3_H

#include "ViewObject.h"
#include "ObjectList.h"
#include "Music.h"
#include "Block.h"

class Map3 : public df::ViewObject {

private:

	Block *p_escapeDoor[4];
	Block *p_cageFloor[15];
	df::Music *p_music;
	int difficulty = 0;
	int playerCount = 0;
	bool haveBow = false;
	bool haveWand = false;

public:

	explicit Map3(int difficulty);

	~Map3() override;

	void start();

	void stop(int type, int playTime);

	int draw() override;

	void escape();

	void groundDefeat();

	int getDifficulty() const;

	int getPlayerCount() const;

	void setPlayerCount(int playerCount);
};

#endif //MEANT_2B_DF_MAP3_H
