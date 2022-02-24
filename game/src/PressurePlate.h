//
// Created by 方申 on 2/23/22.
//

#ifndef MEANT_2B_DF_PRESSUREPLATE_H
#define MEANT_2B_DF_PRESSUREPLATE_H

#include "Object.h"
#include "Color.h"

class PressurePlate : public df::Object {
private:
    df::Color color;
public:
    PressurePlate();

    PressurePlate(df::Vector position, df::Color new_color);

    int draw();

    int eventHandler(const df::Event *p_e);

};


#endif //MEANT_2B_DF_PRESSUREPLATE_H
