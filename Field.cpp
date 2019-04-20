#include "Field.h"


int Field::maxX = 1000;
int Field::maxY = 1000;


Field::Field(const int & w, const int & h){
	width = w;
	height = h;
	cells.resize(height);
	for (auto& it1 : cells) {
		it1.resize(width);
		for (auto& it2 : it1) {
			it2 = nullptr;
		}
	}
}

Field::~Field() {
	
}

size_t Field::getHeight() const{
	return height;
}

void Field::setBrick(BrickPos & brickPos, int hp, int sp){
	Brick* brick = new Brick(brickPos, hp, sp);
	for (size_t y = brickPos.y; y <= brickPos.y + (brickPos.size - 1) *(brickPos.verticOrient); ++y) {
		for (size_t x = brickPos.x; x <= brickPos.x + (brickPos.size - 1)*(!brickPos.verticOrient); ++x) {
			cells[y][x] = brick;
		}
	}
	bricks.push_back(brick);
}



void Field::brakeBrick(Brick* b) {
	cells[b->getBrickPos().y][b->getBrickPos().x] = nullptr;
	delete b;
}

void Field::brakeAllBricks() {
	bricks.clear();
}

void Field::setMaxX(int x) {
	maxX = x;
}

void Field::setMaxY(int y) {
	maxY = y;
}


Brick * Field::getCell(int x, int y) {
	if (x >= width || x < 0 || y >= height || y < 0) {
		return nullptr;
	}
	return cells[y][x];
}



std::vector<Brick*>& Field::getBricks() {
	return bricks;
}

std::vector<std::vector<Brick*>> Field::getCells() {
	return cells;
}

size_t Field::getWidth() const{
	return width;
}



