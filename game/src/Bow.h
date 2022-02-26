#ifndef MEANT_2B_DF_BOW_H
#define MEANT_2B_DF_BOW_H

#include "Object.h"
#include "Event.h"
#include "Player.h"
#include "Vector.h"

class Bow : public df::Object {

private:

	bool nearPlayer;
	Player *player;
	int nearCountdown;
	df::Vector acceleration;

public:

	Bow(df::Vector location);

	int eventHandler(const df::Event *p_e) override;

	int draw() override;
};

#endif //MEANT_2B_DF_BOW_H
