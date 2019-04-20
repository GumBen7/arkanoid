#include "Player.h"


Player::Player() {
	vessel = nullptr;
}

Player::~Player(){
	delete vessel;
}

void Player::vesselShoot() {
	vessel->shoot();
}

void Player::moveVessel(int d) {
	vessel->move(d);
}

void Player::vesselReflect(Ball * b, BallPos pos) {
	b->setDir(vessel->reflect(pos, b->getDir()));
	bindBall(b);
}

void Player::bindBall(Ball * b) {
	if (std::find(bondedBalls.begin(), bondedBalls.end(), b) == bondedBalls.end()) {
		bondedBalls.push_back(b);
	}
}

void Player::attcheBallToVessel(Ball * b) {
	vessel->attacheBall(b);
}

void Player::addScore(int s) {
	score += s;
}

std::vector<Ball*> Player::getBondedBalls() {
	return bondedBalls;
}

void Player::createVessel(size_t x, size_t y, size_t s) {
	if (vessel == nullptr) {
		vessel = new Vessel(x, y, s);
	}
}

int Player::getScore() const {
	return score;
}

Vessel* Player::getVessel(){
	return vessel;
}

