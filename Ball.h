#pragma once

struct UnitVector {
	double dX;
	double dY;
	UnitVector(double x0, double y0) :
		dX(x0),
		dY(y0) {}
};

struct BallPos {
	int x;
	int y;
	int size;
	BallPos(size_t x0, size_t y0, size_t s) :
		x(x0),
		y(y0),
		size(s) {}
};

class Ball {
private:
	BallPos ballPos;
	UnitVector dir;
	bool attached;

	static int maxX;
	static int maxY;
	static int xSpeedRatio;
	static int ySpeedRatio;
public:
	Ball(int x0, int y0, size_t s);
	//Ball(size_t x0, size_t y0, size_t s, bool isAtt) : ballPos(x0, y0, s), attached(isAtt) {}
	~Ball();

	void getFree();
	void getAttached();

	void move();
	void move(int dx, int dy);

	void pushOffUp(int y);
	void pushOffDown(int y);
	void pushOffLeft(int x);
	void pushOffRight(int x);

	bool isAttached();

	BallPos getBallPos();
	UnitVector getDir();

	void setDir(UnitVector d);

	static void setMaxX(size_t x);
	static void setMaxY(size_t y);
	static void setXSpeedRatio(size_t r);
	static void setYSpeedratio(size_t r);

	static size_t getMaxX();
	static size_t getMaxY();
	static int getXSpeedRatio();
	static int getYSpeedRatio();
};

