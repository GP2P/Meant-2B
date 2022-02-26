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
	bool haveBow;
	bool haveWand;
	bool inMap;
    std::string direction;

public:

	Player();

	Player(int ID);

	~Player() override;

	int eventHandler(const df::Event *p_e) override;

	bool onGround();

	int jump();

	void shoot(df::Vector target);

	int getID() const;

	void setID(int id);

	bool isHaveStone() const {
		return haveStone;
	}

	bool isHaveBow() const {
		return haveBow;
	}

	bool isHaveWand() const {
		return haveWand;
	}

	void setHaveStone(bool haveStone) {
		Player::haveStone = haveStone;
	}

	void setHaveBow(bool haveBow) {
		Player::haveBow = haveBow;
	}

	void setHaveWand(bool haveWand) {
		Player::haveWand = haveWand;
	}

	bool isInMap() const {
		return inMap;
	}

	void setInMap(bool inMap) {
		Player::inMap = inMap;
	}

	bool haveItem();

    int draw() override;
};

#endif //DF_PLAYER_H
