#ifndef MEANT_2B_DF_BAT_H
#define MEANT_2B_DF_BAT_H

#include "Object.h"

class Bat : public df::Object {

private:

	int moveCountdown;

public:

	Bat();

	~Bat();

	int eventHandler(const df::Event *p_e) override;
};

#endif //MEANT_2B_DF_BAT_H
