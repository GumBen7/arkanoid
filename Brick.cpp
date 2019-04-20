#include "Brick.h"

Brick::~Brick()
{
}

int Brick::getHP(){
	return hitPoints;
}

int Brick::getScorePoint() {
	return scorePoints;
}

BrickPos Brick::getBrickPos(){
	return brickPos;
}

void Brick::takeShot(){
	--hitPoints;
}

bool Brick::isBroken(){
	return (hitPoints == 0);
}
