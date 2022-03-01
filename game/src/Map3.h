#ifndef MEANT_2B_DF_MAP3_H
#define MEANT_2B_DF_MAP3_H

#include "ViewObject.h"
#include "ObjectList.h"
#include "Music.h"
#include "Block.h"

class Map3 : public df::ViewObject {

private:

	bool bowAlive;
	bool wandAlive;
	Block *p_escapeDoor[4];
	df::Music *p_music;
	int difficulty = 0;
public:
    int getDifficulty() const;

public:

	explicit Map3(int difficulty);

	~Map3() override;

	void start();

	void stop();

	int draw() override;

	void escape();
};

#endif //MEANT_2B_DF_MAP3_H
