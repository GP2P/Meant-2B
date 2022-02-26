//
// Created by 方申 on 2/26/22.
//

#ifndef MEANT_2B_DF_BOSSPROJECTILE_H
#define MEANT_2B_DF_BOSSPROJECTILE_H


#include "Object.h"
#include "EventCollision.h"

class BossProjectile : public df::Object {

public:
    BossProjectile(df::Vector boss_pos);

    int eventHandler(const df::Event *p_e);
};


#endif //MEANT_2B_DF_BOSSPROJECTILE_H
