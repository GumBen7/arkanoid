#pragma once
#include "Game.h"
#include "Player.h"
#include "Vessel.h"
#include "Ball.h"
#include <fstream>
#include <string>



class Controller{
private:
	Game* game;
	Field* field;
	Player* player1;


	bool isInMainMenu;

	const size_t FIELD_WIDTH = 13, FIELD_HEIGHT = 24;

	const size_t GAME_FIELD_X_RESOL = 1000;
	const size_t GAME_FIELD_Y_RESOL = 1000;
	const size_t X_TO_VESSEL_SIZE_RATIO = 7;
	const size_t X_TO_BALL_SIZE_RATIO = 7 * 4 * 2;
	const size_t BALL_X_TO_STEP_RATIO = GAME_FIELD_X_RESOL / (2*X_TO_BALL_SIZE_RATIO);
	const size_t BALL_Y_TO_STEP_RATIO = GAME_FIELD_Y_RESOL / (2*X_TO_BALL_SIZE_RATIO);
	const size_t VESSEL_X_TO_STEP_RATIO = GAME_FIELD_X_RESOL / (4 * X_TO_VESSEL_SIZE_RATIO);
	const size_t BRICK_FIELD_DOWN_MARGIN = 2;
	const size_t Y_TO_BRICK_RATIO = GAME_FIELD_X_RESOL / (FIELD_HEIGHT + BRICK_FIELD_DOWN_MARGIN);
	
public:
	Controller();
	~Controller();	

	void startGame();
	void playGame();
	void gameOver();
	
	void moveGameBalls();
	void movePlayerVessel(Player* p, int dir);

	bool isGameInMainMenu();

	int getGameTryCount();
	int getHighScore();

	size_t getXResol();
	size_t getYResol();

	std::vector<std::vector<Brick*>> getFieldCells();
	int getFieldWidth();
	int getFieldHeight();

	int getBrickXByOrder(int x);
	int getBrickYByOrder(int y);

	Brick* getFieldCell(int x, int y);

	Player* getPlayer1();
	Vessel* getPlayerVessel(Player* p);
	std::vector<Ball*> getGameBalls();
	
};

