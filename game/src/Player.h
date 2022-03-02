#ifndef DF_PLAYER_H
#define DF_PLAYER_H

#include "Object.h"
#include "DisplayManager.h"
#include "Block.h"
#include "Reticle.h"
#include "WorldManager.h"
#include "Clock.h"

class Player : public df::Object {

private:

	int playerID;
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
	int mapNum;
	Reticle *p_reticle = nullptr;
	int hintCD;
	df::Clock *clock;
	long int totalTime;

public:

	Player();

	Player(int ID);

	~Player() override;

	int eventHandler(const df::Event *p_e) override;

	bool onGround();

	int jump();

	void shoot(df::Vector target);

	int getPlayerID() const;

	void setPlayerID(int id);

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
		shootCountdown = shootSlowdown;
		if (haveBow && mapNum == 3) {
			p_reticle = new Reticle(df::RED);
			p_reticle->draw();
		} else if (!haveBow) {
			if (p_reticle != nullptr)
				WM.markForDelete(p_reticle);
			p_reticle = nullptr;
		}
	}

	void setHaveWand(bool haveWand) {
		Player::haveWand = haveWand;
		if (haveWand) {
			if (mapNum == 2 || mapNum == 4 || mapNum == 5) {
				p_reticle = new Reticle(df::MAGENTA);
				p_reticle->draw();
			}
		} else {
			if (p_reticle != nullptr)
				WM.markForDelete(p_reticle);
			p_reticle = nullptr;
		}
	}

	bool isInMap() const {
		return inMap;
	}

	void setInMap(bool inMap) {
		Player::inMap = inMap;
	}

	bool haveItem();

	int getMapNum() const {
		return mapNum;
	}

	void setMapNum(int mapNum) {
		Player::mapNum = mapNum;
	}

	long getTotalTime() const;

	void setTotalTime(long totalTime);

	int draw() override;

	df::Clock *getClock() const;

	void setClock(df::Clock *clock);
};

#endif //DF_PLAYER_H
