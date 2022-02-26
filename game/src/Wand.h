//
// Created by 方申 on 2/25/22.
//

#ifndef MEANT_2B_DF_WAND_H
#define MEANT_2B_DF_WAND_H


#include "Object.h"
#include "Event.h"
#include "Player.h"
#include "Vector.h"

class Wand : public df::Object {

private:

    bool nearPlayer;
    Player *player;
    int nearCountdown;
    df::Vector acceleration;

public:

    Wand(df::Vector location);

    int eventHandler(const df::Event *p_e) override;

    int draw() override;

};


#endif //MEANT_2B_DF_WAND_H
