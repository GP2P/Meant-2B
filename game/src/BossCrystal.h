
#ifndef MEANT_2B_DF_BOSSCRYSTAL_H
#define MEANT_2B_DF_BOSSCRYSTAL_H

#include "Object.h"
#include "EventCollision.h"

class BossCrystal : public df::Object {
private:
	int stage;

	int movecd;
public:

	BossCrystal(df::Vector boss_pos, int difficulty);

	int eventHandler(const df::Event *p_e);
};

#endif //MEANT_2B_DF_BOSSCRYSTAL_H
