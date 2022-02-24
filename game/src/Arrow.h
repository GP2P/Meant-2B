//
// Created by 方申 on 2/23/22.
//

#ifndef MEANT_2B_DF_ARROW_H
#define MEANT_2B_DF_ARROW_H


#include "Object.h"
#include "EventCollision.h"

class Arrow : public df::Object {
private:

public:
    Arrow(df::Vector player_pos);

    int eventHandler(const df::Event *p_e);

};


#endif //MEANT_2B_DF_ARROW_H
