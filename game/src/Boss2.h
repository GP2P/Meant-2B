
#ifndef MEANT_2B_DF_BOSS2_H
#define MEANT_2B_DF_BOSS2_H


#include "Object.h"
#include "Boss.h"

class Boss2 : public df::Object {
private:
	Boss *boss;
public:
	Boss2(Boss *Boss);

	int eventHandler(const df::Event *p_e) override;
};


#endif //MEANT_2B_DF_BOSS2_H
