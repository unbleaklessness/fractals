#include "fractals_3d.h"

#include <GL/glut.h>

namespace fractals_3d {

	void display() {
		
		draw_callback();

	}

	void update_projection() {
		
	}

	void reshape(int width, int height)
	{
		
	}

	void keyboard(int key, int x, int y)
	{
		
	}

	void start() {

		int argc = 0;
		char **argv = new char*[0];
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(window_width, window_height);
		glutCreateWindow("2D Fractals");

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		glutDisplayFunc(&display);
		glutSpecialFunc(&keyboard);
		glutReshapeFunc(&reshape);

		glutMainLoop();
	}
}