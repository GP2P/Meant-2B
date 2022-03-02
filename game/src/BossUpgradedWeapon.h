
#ifndef MEANT_2B_DF_BOSSUPGRADEDWEAPON_H
#define MEANT_2B_DF_BOSSUPGRADEDWEAPON_H

#include "Object.h"
#include "EventCollision.h"

class BossUpgradedWeapon : public df::Object {
private:
    int stage;

    int movecd;
public:

    BossUpgradedWeapon(df::Vector boss_pos, int difficulty);

    int eventHandler(const df::Event *p_e);
};

#endif //MEANT_2B_DF_BOSSUPGRADEDWEAPON_H
