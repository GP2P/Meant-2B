#ifndef MEANT_2B_DF_BOSS_H
#define MEANT_2B_DF_BOSS_H

#include "Object.h"

class Boss : public df::Object {

private:

	int moveCountdown;

	int difficulty = 0;

	int maxHP;

	int hp;

	int fireCountdown;

	int fireSlowdown = 60;

public:

	Boss(int difficulty);

	void defeat();

	int getHp() const;

	void setHp(int hp);

	int eventHandler(const df::Event *p_e) override;

	void fire();
};

#endif //MEANT_2B_DF_BOSS_H
