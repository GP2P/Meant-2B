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
	int difficulty;
	df::Vector acceleration = df::Vector(0, 0.1);
	float jumpSpeed = 0.95;
	int shootCountdown;
	int shootSlowdown = 30;
	int walkingCountdown = 0;
	bool haveStone = false;
	bool haveBow = false;
	bool haveWand = false;
	bool inMap1 = true;
	bool inMap3 = true;
	std::string direction = "right";
	int mapNum = 0;
	Reticle *p_reticle = nullptr;
	int hintCD = 60;
	df::Clock *clock = new df::Clock;
	long int totalTime;
	bool map3OnGround = false;

public:

	Player(int ID, int difficulty);

	~Player() override;

	void defeat();

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

	bool isInMap1() const {
		return inMap1;
	}

	void setInMap1(bool inMap) {
		Player::inMap1 = inMap;
	}

	bool isInMap3() const {
		return inMap3;
	}

	void setInMap3(bool inMap) {
		Player::inMap3 = inMap;
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

	bool isMap3OnGround() const;

	void setMap3OnGround(bool map3OnGround);
};

#endif //DF_PLAYER_H
