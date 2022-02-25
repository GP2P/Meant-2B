//
// Created by 方申 on 2/23/22.
//

#ifndef MEANT_2B_DF_EVENTOPENGATE_H
#define MEANT_2B_DF_EVENTOPENGATE_H

#include "Event.h"
#include "Color.h"


class EventOpenGate : public df::Event{
private:
    df::Color color; //only trigger with same color can open gate
    bool open; // open(true) or close (false)

public:
    EventOpenGate();
    df::Color getColor() const;
    void setColor(df::Color Color);
    bool getOpen() const;
    void setOpen(bool open);


};


#endif //MEANT_2B_DF_EVENTOPENGATE_H
