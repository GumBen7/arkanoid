#include "GlutView.h"

Controller* GlutView::controller = nullptr;
double GlutView::PIXEL_TO_X_RESOL_RATIO = 1.;
double GlutView::PIXEL_TO_Y_RESOL_RATIO = 1.;



GlutView::GlutView(int argc, char * argv[], Controller * c)  {
	controller = c;
	PIXEL_TO_X_RESOL_RATIO = (double)(GAME_FIELD_SIZE_X) / c->getXResol();
	PIXEL_TO_Y_RESOL_RATIO = (double)(GAME_FIELD_SIZE_Y) / c->getYResol();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("Arkanoid");
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(arrow);
}

void GlutView::reshape(int w, int h) {
	/* Because Gil specified "screen coordinates" (presumably with an
	   upper-left origin), this short bit of code sets up the coordinate
	   system to correspond to actual window coodrinates.  This code
	   wouldn't be required if you chose a (more typical in 3D) abstract
	   coordinate system. */
	glutReshapeWindow(WIDTH, HEIGHT);
	glViewport(0, 0, w, h);       // Establish viewing area to cover entire window. 
	glMatrixMode(GL_PROJECTION);  // Start modifying the projection matrix. 
	glLoadIdentity();             // Reset project matrix. 
	glOrtho(0, w, 0, h, -1, 1);   // Map abstract coords directly to window coords. 
	glScalef(1, -1, 1);           // Invert Y axis so increasing Y goes down. 
	glTranslatef(0, -h, 0);       // Shift origin up to upper-left corner. */
}

void GlutView::display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (!controller->isGameInMainMenu()) {
		showGameField();
		showInterface();
		/*glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 1.0);  // blue
		glVertex2i(0, 0);
		glColor3f(0.0, 1.0, 0.0);  // green 
		glVertex2i(200, 200);
		glColor3f(1.0, 0.0, 0.0);  // red 
		glVertex2i(20, 200);
		glEnd();*/
	}
	else {
		glColor3f(1, 1, 1);
		std::string s = "Press SPACE to Start";
		glRasterPos2f(MARGIN_DOWN, GAME_FIELD_SIZE_Y/2);
		for (int i = 0; i < s.length(); ++i) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
	}
	glFlush();  /* Single buffered, so needs a flush. */
}

void GlutView::arrow(int a, int x, int y) {
	if (!controller->isGameInMainMenu()) {
		int d = 0;
		switch (a) {
		case 100:
			d = -1;
			break;
		case 102:
			d = 1;
			break;
		}
		controller->getPlayer1()->moveVessel(d);
	}
}

void GlutView::key(unsigned char k, int x, int y) {
	if (k == ' ') {
		if (controller->isGameInMainMenu()) {
			start();
		}
		else {
			controller->getPlayer1()->vesselShoot();
		}
	}
}

void GlutView::timer(int) {
	//display();
	glutPostRedisplay();
	if (!controller->isGameInMainMenu()) {
		controller->moveGameBalls();
		glutTimerFunc(10, timer, 0);
	}
}

void GlutView::showGameField() {
	showVessel();
	showBricks();
	showBalls();
}

void GlutView::showInterface() {
	showBoarder();
	showScores();
	showTryCount();
}

void GlutView::showVessel() {
	glColor3f(1, 1, 0.);
	VesselPos pos = controller->getPlayerVessel(controller->getPlayer1())->getVesselPos();	
	glRectf(MARGIN_X + pos.x*PIXEL_TO_X_RESOL_RATIO, MARGIN_UP + invertY(pos.y)*PIXEL_TO_Y_RESOL_RATIO, MARGIN_X + (pos.x + pos.size)*PIXEL_TO_X_RESOL_RATIO, MARGIN_UP + invertY(pos.y + pos.size/4 )* PIXEL_TO_Y_RESOL_RATIO);
}

void GlutView::showBalls() {
	glColor3f(0, 0, 1);
	std::vector<BallPos> ballsPos;
	std::vector<Ball*> balls = controller->getGameBalls();
	for (auto& it : balls) {
		ballsPos.push_back(it->getBallPos());
	}
	for (auto& it : ballsPos) {
		glRectf(MARGIN_X + it.x*PIXEL_TO_X_RESOL_RATIO, MARGIN_UP + invertY(it.y) * PIXEL_TO_Y_RESOL_RATIO, MARGIN_X + (it.x + it.size)*PIXEL_TO_X_RESOL_RATIO, MARGIN_UP + invertY(it.y + it.size) * PIXEL_TO_Y_RESOL_RATIO);
	}
	
}

void GlutView::showBricks() {
	glColor3f(1, 1, 1);
	//auto cells = controller->getFieldCells();
	for (int i = 0; i < controller->getFieldHeight(); ++i) {
		for (int j = 0; j < controller->getFieldWidth(); ++j) {
			if (controller->getFieldCell(j, i) != nullptr) {
				glRectf(MARGIN_X + controller->getBrickXByOrder(j)*PIXEL_TO_X_RESOL_RATIO, MARGIN_UP + (controller->getBrickYByOrder(i)*PIXEL_TO_Y_RESOL_RATIO), MARGIN_X + controller->getBrickXByOrder(j+1)*PIXEL_TO_X_RESOL_RATIO - 1, MARGIN_UP + (controller->getBrickYByOrder(i+1))*PIXEL_TO_Y_RESOL_RATIO - 1);
			}
		}
	}
}

void GlutView::showBoarder() {
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2d(MARGIN_X, MARGIN_UP + GAME_FIELD_SIZE_Y);
	glVertex2d(MARGIN_X, MARGIN_UP);
	glVertex2d(MARGIN_X, MARGIN_UP);
	glVertex2d(MARGIN_X + GAME_FIELD_SIZE_X, MARGIN_UP);
	glVertex2d(MARGIN_X + GAME_FIELD_SIZE_X, MARGIN_UP);
	glVertex2d(MARGIN_X + GAME_FIELD_SIZE_X, MARGIN_UP + GAME_FIELD_SIZE_Y);
	glEnd();
}

void GlutView::showScores() {
	std::string s1 = "1UP:";
	std::string s2 = std::to_string(controller->getPlayer1()->getScore());
	std::string s3 = "High Score:";
	std::string s4 = std::to_string(controller->getHighScore());
	glRasterPos2f(MARGIN_X, MARGIN_X);
	for (int i = 0; i < s1.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s1[i]);
	}
	glRasterPos2f(MARGIN_X, 3*MARGIN_X);
	for (int i = 0; i < s2.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s2[i]);
	}
	glRasterPos2f(MARGIN_X + MARGIN_UP, MARGIN_X);
	for (int i = 0; i < s3.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s3[i]);
	}
	glRasterPos2f(MARGIN_X + MARGIN_UP, 3*MARGIN_X);
	for (int i = 0; i < s4.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s4[i]);
	}
}

void GlutView::showTryCount() {
	int tries = controller->getGameTryCount();
	glColor3f(1, 1, 0);
	for (int i = 0; i < tries; ++i) {
		glRectf(MARGIN_X * (i+1) + MARGIN_X * (i), MARGIN_UP + GAME_FIELD_SIZE_Y + MARGIN_X, MARGIN_X * (i + 1) + MARGIN_X * (i + 1), MARGIN_UP + GAME_FIELD_SIZE_Y + 2 * MARGIN_X);
	}
}

int GlutView::invertY(int y0) {
	return controller->getYResol() - y0;
}

//void GlutView::showField(Field* field) const {}

void GlutView::start() {
	controller->startGame();
	controller->playGame();
	glutTimerFunc(10, timer, 0);
}

void GlutView::loop() {
	glutMainLoop();
}
