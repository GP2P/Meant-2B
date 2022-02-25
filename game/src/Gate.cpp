//
// Created by 方申 on 2/23/22.
//

#include "Gate.h"
#include "DisplayManager.h"
#include "EventOpenGate.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"


Gate::Gate(){
}

Gate::Gate(df::Vector position, Direction new_direction, df::Color new_color){
    setPosition(position);
    direction = new_direction;
    color = new_color;
    registerInterest("OpenGateEvent");
}

int Gate::draw(){
    switch(direction){

        case UP:
            DM.drawCh(getPosition(),'|',color);
            DM.drawCh(getPosition()+df::Vector(0,-1),'|',color);
            break;
        case DOWN:
            DM.drawCh(getPosition(),'|',color);
            DM.drawCh(getPosition()+df::Vector(0,1),'|',color);
            break;
        case LEFT:
            DM.drawCh(getPosition(),'_',color);
            DM.drawCh(getPosition()+df::Vector(0,-1),'_',color);
            break;
        case RIGHT:
            DM.drawCh(getPosition(),'_',color);
            DM.drawCh(getPosition()+df::Vector(0,1),'_',color);
            break;
        default:
            return 0;
    }
}

int Gate::eventHandler(const df::Event *p_e){
    if (p_e->getType() == "OpenGateEvent") {
        const EventOpenGate *p_oge = dynamic_cast <const EventOpenGate *> (p_e);
        if(p_oge->getColor() == color) {
            if (p_oge->getOpen() == true) {
                LM.writeLog("open gate");
                setSolidness(df::SOFT);
            } else if(p_oge->getOpen() == false) {
                LM.writeLog("close gate");
                setSolidness(df::HARD);
            }
        }
     }
}