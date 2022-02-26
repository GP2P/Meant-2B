#ifndef DF_PLAYER_H
#define DF_PLAYER_H

#include "Object.h"

class Player : public df::Object {

private:

	int ID;
	df::Vector acceleration;
	float jumpSpeed;
	int shootCountdown;
	int shootSlowdown;
	int walkingCountdown;
	bool haveStone;
	bool inMap;

public:

	Player();

	Player(int ID);

	int eventHandler(const df::Event *p_e) override;

	bool onGround();

	int jump();

	void shoot(df::Vector target);

	int getID() const;

	void setID(int id);

	bool isHaveStone() const {
		return haveStone;
	}

	void setHaveStone(bool haveStone) {
		Player::haveStone = haveStone;
	}

	bool isInMap() const {
		return inMap;
	}

	void setInMap(bool inMap) {
		Player::inMap = inMap;
	}
};

#endif //DF_PLAYER_H
