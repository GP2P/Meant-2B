#ifndef DF_MAP1_H
#define DF_MAP1_H

#include "ViewObject.h"
#include "Music.h"

class Map1 : public df::ViewObject {

private:

	df::Music *p_music;

public:

	Map1();

	~Map1() override;

	void start();

	void stop();

	int draw() override;
};

#endif //DF_MAP1_H
