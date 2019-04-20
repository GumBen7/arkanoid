#include "Controller.h"


Controller::Controller() {	
	isInMainMenu = true;
	Vessel::setMaxX(GAME_FIELD_X_RESOL);
	Vessel::setMaxY(GAME_FIELD_Y_RESOL);
	Vessel::setXSPeedRatio(VESSEL_X_TO_STEP_RATIO);
	Ball::setMaxX(GAME_FIELD_X_RESOL);
	Ball::setMaxY(GAME_FIELD_Y_RESOL);
	Ball::setXSpeedRatio(BALL_X_TO_STEP_RATIO);
	Ball::setYSpeedratio(BALL_Y_TO_STEP_RATIO);
	Game::setXBallRatio(X_TO_BALL_SIZE_RATIO);
	Game::setXVesselRatio(X_TO_VESSEL_SIZE_RATIO);
	Field::setMaxX(GAME_FIELD_X_RESOL);
	Field::setMaxY(GAME_FIELD_Y_RESOL);
	Game::setYToBrickRatio(Y_TO_BRICK_RATIO);
	Game::setFieldDownMargin(BRICK_FIELD_DOWN_MARGIN);
}


Controller::~Controller()
{
}

void Controller::startGame() {
	
	int hS;
	std::ifstream ifs;
	ifs.open("high_score.txt");	
	if (ifs.is_open()) {
		while (ifs >> hS) {}
	}
	else {
		hS = 0;
	}
	ifs.close();
	
	
	isInMainMenu = false;
	field = new Field(FIELD_WIDTH, FIELD_HEIGHT);
	player1 = new Player;
	int vesselSize = Vessel::getMaxX() / X_TO_VESSEL_SIZE_RATIO;
	int ballSize = Ball::getMaxX() / X_TO_BALL_SIZE_RATIO;
	player1->createVessel(Vessel::getMaxX() / 2 - vesselSize / 2, 0, vesselSize);
	Ball* ball = new Ball(player1->getVessel()->getVesselPos().x + player1->getVessel()->getVesselPos().size /2, 2*ballSize, ballSize);
	player1->bindBall(ball);
	player1->attcheBallToVessel(ball);
	game = new Game(player1, field, ball);
	game->setHighScore(hS);
	game->newTry();
}

void Controller::playGame(){
	game->playNewRound();
	
}

void Controller::gameOver() {
	std::ofstream ofs("high_score.txt");
	if (ofs.is_open()) {
		ofs << game->getHighScore();
	}
	ofs.close();
	isInMainMenu = true;
	delete field;
	delete player1;
	delete game;
}


void Controller::moveGameBalls() {
	game->moveBalls();
	if (game->isTryOver()) {
		if (game->getTryCount() == 0) {
			gameOver();
		}
		else {
			int ballSize = Ball::getMaxX() / X_TO_BALL_SIZE_RATIO;
			Ball* ball = new Ball(player1->getVessel()->getVesselPos().x + player1->getVessel()->getVesselPos().size / 2, 2 * ballSize, ballSize);
			player1->bindBall(ball);
			player1->attcheBallToVessel(ball);
			game->addBall(ball);
			game->newTry();
		}
	}
	/*if (game->isRoundOver()) {
		game->playNewRound();
	}*/
}

void Controller::movePlayerVessel(Player * p, int dir) {
	
}

bool Controller::isGameInMainMenu() {
	return Controller::isInMainMenu;
}

int Controller::getGameTryCount() {
	return game->getTryCount();
}

int Controller::getHighScore() {
	return game->getHighScore();
}

size_t Controller::getXResol() {
	return GAME_FIELD_X_RESOL;
}

size_t Controller::getYResol() {
	return GAME_FIELD_Y_RESOL;
}

std::vector<std::vector<Brick*>> Controller::getFieldCells() {
	return field->getCells();
}

int Controller::getFieldWidth() {
	return field->getWidth();
}

int Controller::getFieldHeight() {
	return field->getHeight();
}

int Controller::getBrickXByOrder(int x) {
	return game->getBrickXByOrder(x);
}

int Controller::getBrickYByOrder(int y) {
	return game->getBrickYByOrder(y);
}

Brick * Controller::getFieldCell(int x, int y) {
	return field->getCell(x, y);
}

Player* Controller::getPlayer1(){
	return player1;
}

Vessel * Controller::getPlayerVessel(Player * p) {
	return p->getVessel();
}

std::vector<Ball*> Controller::getGameBalls() {
	return game->getBalls();
}




