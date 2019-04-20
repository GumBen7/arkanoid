#pragma once
#include "View.h"

#include "Controller.h"
#include <string>

#include "GL/glut.h"



class GlutView : public View{
private:
	
public:
	GlutView(int argc, char* argv[], Controller* c);

	static Controller* controller;
	static void reshape(int w, int h);
	static void display();
	static void arrow(int a, int x, int y);
	static void key(unsigned char k, int x, int y);
	static void timer(int = 0);

	static void showGameField();
	static void showInterface();
	static void showVessel();
	static void showBalls();
	static void showBricks();

	static void showBoarder();
	static void showScores();
	static void showTryCount();

	static void showStartMessage();

	static int invertY(int y0);

	static const int WIDTH = 500;
	static const int HEIGHT = 600;
	static const int MARGIN_X = 10;
	static const int MARGIN_UP = 60;
	static const int MARGIN_DOWN = 60;
	static const int GAME_FIELD_SIZE_X = WIDTH - MARGIN_X - MARGIN_X;
	static const int GAME_FIELD_SIZE_Y = HEIGHT - MARGIN_UP - MARGIN_DOWN;

	static double PIXEL_TO_X_RESOL_RATIO;
	static double PIXEL_TO_Y_RESOL_RATIO;
	//virtual void showField(Field* field) const override;

	static void start();
	static void loop();


};

