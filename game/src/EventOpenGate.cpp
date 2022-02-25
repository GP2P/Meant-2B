//
// Created by 方申 on 2/23/22.
//

#include "EventOpenGate.h"

EventOpenGate::EventOpenGate(){
    setType("OpenGateEvent");
}

df::Color EventOpenGate::getColor() const{
    return color;
}
void EventOpenGate::setColor(df::Color Color){
    color = Color;
}

bool EventOpenGate::getOpen() const{
    return open;
}
void EventOpenGate::setOpen(bool new_open){
    open = new_open;
}

