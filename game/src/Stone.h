//
// Created by 方申 on 2/25/22.
//

#ifndef MEANT_2B_DF_STONE_H
#define MEANT_2B_DF_STONE_H

#include "Object.h"
#include "Event.h"
#include "Player.h"
#include "Vector.h"


class Stone: public df::Object {
private:
    bool nearPlayer;
    Player *player;
    int nearcountdown;
    df::Vector acceleration;
public:
    Stone(df::Vector location);

    int eventHandler(const df::Event *p_e) override;

    int draw();

    bool onGround();
};
#endif //MEANT_2B_DF_STONE_H
