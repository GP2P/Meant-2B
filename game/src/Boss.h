#ifndef MEANT_2B_DF_BOSS_H
#define MEANT_2B_DF_BOSS_H

#include "Object.h"

class Boss : public df::Object {

private:

	int moveCountdown;

    int hp;
public:
    int getHp() const;

    void setHp(int hp);

	Boss();

	int eventHandler(const df::Event *p_e) override;
};

#endif //MEANT_2B_DF_BOSS_H
