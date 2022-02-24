#ifndef DF_PLAYER_H
#define DF_PLAYER_H

#include "Object.h"

class Player : public df::Object {

private:

	df::Vector acceleration;

	bool allowdoublejump;

	int jumpCount;

	float jumpspeed;


public:

	Player();

	int eventHandler(const df::Event *p_e);

	bool onGround();

	int move(int dy);

	int jump();


};

#endif //DF_PLAYER_H
