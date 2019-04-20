#include "Vessel.h"


int Vessel::maxX = 1000;
int Vessel::maxY = 1000;
int Vessel::xSpeedRatio = 55;

Vessel::~Vessel()
{
}

void Vessel::shoot() {
	for (auto& it : attachedBalls) {
		it->setDir(this->reflect(it->getBallPos(), it->getDir()));
		it->getFree();
	}
	attachedBalls.clear();
}



void Vessel::attacheBall(Ball * b) {
	b->getAttached();
	attachedBalls.push_back(b);
}

void Vessel::move(int dir) {
	int d = dir * xSpeedRatio;
	if (vesselPos.x + d < 0) {
		d = - vesselPos.x;
	}
	if (vesselPos.x + vesselPos.size + d >= maxX) {
		d = maxX - vesselPos.x - vesselPos.size;
	}
	vesselPos.x += d;
	
	if (!attachedBalls.empty()) {
		for (auto& it : attachedBalls) {
			it->move(d, 0);
		}
	}
	//cout << vesselPos.x << endl;
}

UnitVector Vessel::reflect(BallPos pos, UnitVector dir) {
	//std::cout << dir.dX << " " << dir.dY << " to reflect" << std::endl;
	double x = (double)((pos.x + pos.size/2) - (vesselPos.x + vesselPos.size/2)) + dir.dX * Ball::getXSpeedRatio();
	double y = (double)(pos.y) - dir.dY * Ball::getYSpeedRatio();
	double m = sqrt(x*x + y*y);
	//std::cout << x/m << " " << y/m << " reflceted " << x << " " << y << " " << m << std::endl;
	return UnitVector((x/m),(y/m));
}

void Vessel::setXSPeedRatio(int r) {
	xSpeedRatio = r;
}

void Vessel::setMaxX(size_t x) {
	maxX = x;
}

void Vessel::setMaxY(size_t y) {
	maxY = y;
}

size_t Vessel::getMaxX() {
	return maxX;
}

size_t Vessel::getMaxY() {
	return maxY;
}

VesselPos Vessel::getVesselPos(){
	return vesselPos;
}


