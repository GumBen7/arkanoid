#pragma once

#include "Ball.h"
#include <vector>

struct VesselPos{
	int x;
	int y;
	int size;
	bool verticOrient;
	VesselPos(size_t x0, size_t y0, size_t s, bool vo) :
		x(x0),
		y(y0),
		size(s),
		verticOrient(vo) {}
};

class Vessel {

private:
	VesselPos vesselPos;
	std::vector<Ball*> attachedBalls;

	static int maxX;
	static int maxY;
	static int xSpeedRatio;
public:

	Vessel(size_t x0, size_t y0, size_t s) : vesselPos(x0, y0, s, false) {}
	~Vessel();	

	void shoot();
	void attacheBall(Ball* b);
	void move(int dir);

	UnitVector reflect(BallPos pos, UnitVector dir);

	static void setXSPeedRatio(int r);

	static void setMaxX(size_t x);
	static void setMaxY(size_t y);

	static size_t getMaxX();
	static size_t getMaxY();

	VesselPos getVesselPos();
};

