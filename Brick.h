#pragma once

struct BrickPos {
	size_t x;
	size_t y;
	size_t size;
	bool verticOrient;
	BrickPos(size_t x0, size_t y0, size_t s, bool ho) :
		x(x0),
		y(y0),
		size(s),
		verticOrient(ho) {}
};
class Brick{
private:
	int hitPoints;
	int scorePoints;
	BrickPos brickPos;
public:
	Brick(BrickPos pos, int hp, int sp) : 
		hitPoints(hp),
		scorePoints(sp),
		brickPos(pos) {}
	~Brick();

	int getHP();
	int getScorePoint();
	BrickPos getBrickPos();
	void takeShot();
	bool isBroken();
};

