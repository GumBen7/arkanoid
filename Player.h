#pragma once

#include "Vessel.h"

#include <algorithm>

class Player {
private:
	int score = 0;
	Vessel* vessel;

	std::vector<Ball*> bondedBalls;
public:
	Player();
	~Player();

	void vesselShoot();
	void moveVessel(int d);

	void vesselReflect(Ball* b, BallPos pos);

	void bindBall(Ball* ball);	
	void attcheBallToVessel(Ball* b);

	void addScore(int s);

	std::vector<Ball*> getBondedBalls();

	void createVessel(size_t x, size_t y, size_t s);
	int getScore() const;
	Vessel* getVessel();
};

