#ifndef DF_PLAYER_H
#define DF_PLAYER_H

#include "Object.h"

class Player : public df::Object {

private:

	df::Vector acceleration;

	bool allowdoublejump;

	int jumpCount;

	float jumpspeed;

	int shoot_countdown;

	int shoot_slowdown;

    int walkingcountdown;

    bool havestone;

public:

	Player();

	int eventHandler(const df::Event *p_e);

	bool onGround();

	int move(int dy);

	int jump();

	void shoot(df::Vector target);

    bool isHavestone() const {
        return havestone;
    }

    void setHavestone(bool havestone) {
        Player::havestone = havestone;
    }


};

#endif //DF_PLAYER_H
