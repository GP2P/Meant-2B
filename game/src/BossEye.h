
#ifndef MEANT_2B_DF_BOSSEYE_H
#define MEANT_2B_DF_BOSSEYE_H


#include "Object.h"
#include "Boss.h"

class BossEye: public df::Object {
private:
    Boss *boss;
public:
    BossEye(Boss *Boss);
    int eventHandler(const df::Event *p_e) override;
};



#endif //MEANT_2B_DF_BOSSEYE_H
