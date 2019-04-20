#pragma once

#include "Player.h"
#include "Field.h"


class Game{
private:
	Player* player1;
	Field* field;
	std::vector<Ball*> balls;
	int brickCount;
	int round = 0;
	int tryCount = 3;
	int highScore;
	bool over;
	bool roundIsOver;
	bool tryIsOver;
	static int xToVesselSizeRatio;
	static int xToBallSizeRatio;
	static int yToBrickRatio;
	static int maxX;
	static int maxY;
	static int fieldDownMargin;
public:
	Game(Player* p1, Field* f, Ball* b);
	~Game();

	int getBrickXByOrder(int x);
	int getBrickYByOrder(int y);

	Brick* getCellByCoord(int x, int y);

	void playNewRound();
	void setBricks();
	void endRound();

	void addBall(Ball* b);

	void newTry();
	int getTryCount();

	void moveBalls();
	void setHighScore(int s);
	int getHighScore();

	OrderCoord getCellOrderCoord(int x, int y);

	Brick* getHitBrick(Ball* b);

	static void setXVesselRatio(int r);
	static void setXBallRatio(int r);

	static void setFieldDownMargin(int m);

	static void setYToBrickRatio(int r);
	static void setMaxX(int x);
	static void setMaxY(int y);

	bool isTryOver();
	bool isRoundOver();

	int getRound();
	Field& getField();
	std::vector<Ball*> getBalls();
};

