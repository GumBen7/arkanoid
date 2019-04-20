#include <iostream>

#include "Controller.h"
#include "GlutView.h"

int main(int argc, char* argv[]) {

	Controller* controller = new Controller();

	View* view = new GlutView(argc, argv, controller);

	glutMainLoop();

	return 0;
}