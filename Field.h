#pragma once
#include <vector>
#include "Brick.h"

struct OrderCoord {
	int x;
	int y;
	OrderCoord(int x0, int y0) : x(x0), y(y0) {}
};

class Field
{
private: 
	size_t width, height;	
	std::vector<std::vector<Brick*>> cells;
	std::vector<Brick*> bricks;
	static int maxX;
	static int maxY;
	
public:
	Field(const int& w, const int& h);
	~Field();

	void setBrick(BrickPos& brickPos, int hp, int sp);
	
	void brakeBrick(Brick* b);
	void brakeAllBricks();


	static void setMaxX(int x);
	static void setMaxY(int y);

	

	Brick* getCell(int x, int y);
	OrderCoord getCellOrderCoord(Brick* b);

	std::vector<Brick*>& getBricks();
	std::vector<std::vector<Brick*>> getCells();
	size_t getWidth() const;
	size_t getHeight() const;
};

