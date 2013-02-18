#include "GLWindow.h"

GLWindow * GLWindow::instance = NULL;

GLWindow * GLWindow::getInstance(){
	if (!instance) instance = new GLWindow();
	return instance;
}
