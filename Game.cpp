#include "Game.h"


int Game::xToVesselSizeRatio = 7;
int Game::xToBallSizeRatio = 7 * 4 * 2;
int Game::yToBrickRatio = 38;
int Game::maxX = 1000;
int Game::maxY = 1000;
int Game::fieldDownMargin = 2;


Game::Game(Player* p1, Field* f, Ball* b) : player1(p1), field(f) {
	over = false;
	tryIsOver = false;
	balls.push_back(b);
	brickCount = 0;
}


Game::~Game()
{
}

int Game::getBrickXByOrder(int x) {
	return x * maxX / field->getWidth();
}

int Game::getBrickYByOrder(int y) {
	return y * maxY/(field->getHeight() + fieldDownMargin);
}




void Game::playNewRound() {
	endRound();
	++round;
	setBricks();
}

void Game::setBricks() {
	for (int i = 4; i < 10; ++i) {
		for (size_t j = 0; j < field->getWidth(); ++j) {
			BrickPos pos(j, i, 1, false);
			++brickCount;
			if (i == 4) {
				field->setBrick(pos, 2, 50);
			}
			else {
				field->setBrick(pos, 1, 100);
			}
		}
	}//*/
	/*BrickPos pos(5, 5, 1, false);
	field->setBrick(pos, 1, 100);
	BrickPos pos2(6, 6, 1, false);
	field->setBrick(pos2, 1, 100);*/
}

void Game::endRound() {
	field->brakeAllBricks();
}

void Game::addBall(Ball * b) {
	balls.push_back(b);
}

void Game::newTry() {
	--tryCount;
	tryIsOver = false;
}

int Game::getTryCount() {
	return tryCount;
}

void Game::moveBalls() {
	for (auto& it : balls) {
		if (!it->isAttached()) {
			OrderCoord prevCellPos = getCellOrderCoord(it->getBallPos().x + it->getBallPos().size/2, it->getBallPos().y + it->getBallPos().size/2);
			it->move();
			VesselPos vesselPos = player1->getVessel()->getVesselPos();
			BallPos ballPos = it->getBallPos();
			UnitVector ballDir = it->getDir();
			if (ballPos.y <= vesselPos.y + 2*ballPos.size) {
				if (ballPos.x >= vesselPos.x - ballPos.size && ballPos.x < vesselPos.x + vesselPos.size) {
					player1->vesselReflect(it, BallPos((double)ballPos.x - (double)(vesselPos.y + 2*ballPos.size - ballPos.y) * ballDir.dX / ballDir.dY, vesselPos.y + 2*ballPos.size, ballPos.size));
				}
			}
			Brick* hitBrick = getHitBrick(it);
			
			if (hitBrick != nullptr) {
				if (prevCellPos.y > hitBrick->getBrickPos().y) {
					it->pushOffUp(maxY - getBrickYByOrder(hitBrick->getBrickPos().y + 1)); 					
				}
				if (prevCellPos.y < hitBrick->getBrickPos().y) {
					it->pushOffDown(maxY - getBrickYByOrder(hitBrick->getBrickPos().y));
				}
				if (prevCellPos.x > hitBrick->getBrickPos().x) {
					it->pushOffLeft(getBrickXByOrder(hitBrick->getBrickPos().x + 1));
				}
				if (prevCellPos.x < hitBrick->getBrickPos().x) {
					it->pushOffRight(getBrickXByOrder(hitBrick->getBrickPos().x));
				}
				
				hitBrick->takeShot();
				if (hitBrick->isBroken()) {

					std::vector<Ball*> balls = player1->getBondedBalls();
					if (std::find(balls.begin(), balls.end(), it) != balls.end()) {
						player1->addScore(hitBrick->getScorePoint());
						if (player1->getScore() > highScore) {
							highScore = player1->getScore();
						}
					}
					--brickCount;
					field->brakeBrick(hitBrick);
				}
				
			}
			if (it->getBallPos().y < 0) {
				tryIsOver = true;
				balls.pop_back();
				delete it;
				if (balls.size() == 0) {
					tryIsOver = true;
				}
			}

		}
	}
}

void Game::setHighScore(int s) {
	highScore = s;
}

int Game::getHighScore() {
	return highScore;
}

OrderCoord Game::getCellOrderCoord(int x, int y) {
	return OrderCoord(x / (maxX / field->getWidth()), (maxY - y) / (maxY / (field->getHeight() + fieldDownMargin)));
}

Brick * Game::getCellByCoord(int x, int y) {
	return field->getCell(x / (maxX / field->getWidth()), (maxY - y) / (maxY / (field->getHeight() + fieldDownMargin)));
}
Brick * Game::getHitBrick(Ball * b) {
	BallPos pos = b->getBallPos();
	return getCellByCoord(pos.x + pos.size/2, pos.y + pos.size/2);
}

void Game::setXVesselRatio(int r) {
	xToVesselSizeRatio = r;
}

void Game::setXBallRatio(int r) {
	xToBallSizeRatio = r;
}

void Game::setFieldDownMargin(int m) {
	fieldDownMargin = m;
}

void Game::setYToBrickRatio(int r) {
	yToBrickRatio = r;
}

void Game::setMaxX(int x) {
	maxX = x;
}

void Game::setMaxY(int y) {
	maxY = y;
}

bool Game::isTryOver() {
	return tryIsOver;
}

bool Game::isRoundOver() {
	return (brickCount <= 0);
}

int Game::getRound() {
	return round;
}

Field& Game::getField(){
	return *field;
}

std::vector<Ball*> Game::getBalls() {
	return balls;
}

