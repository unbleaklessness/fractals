#include "fractals_2d.h"

#include <GL/glut.h>

#include <cmath>
#include <iostream>

namespace fractals_2d {

	void display() {
		glClear(GL_COLOR_BUFFER_BIT);

		draw_callback();

		glutSwapBuffers();
	}

	void update_projection() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Adjust projection according to observable area:
		glOrtho(-view_range + view_x,
			view_range + view_x,
			-view_range + view_y,
			view_range + view_y, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
	}

	void reshape(int width, int height)
	{
		glViewport(0, 0, width, height);
		update_projection();
		glutPostRedisplay();
	}

	void keyboard(int key, int x, int y)
	{
		// Moving and zooming observable area:
		switch (key)
		{
		case GLUT_KEY_UP:
			view_y += view_range / move_step;
			break;

		case GLUT_KEY_DOWN:
			view_y -= view_range / move_step;
			break;

		case GLUT_KEY_LEFT:
			view_x -= view_range / move_step;
			break;

		case GLUT_KEY_RIGHT:
			view_x += view_range / move_step;
			break;

		case GLUT_KEY_F1:
			view_range -= std::abs(view_range / zoom_step);
			break;

		case GLUT_KEY_F2:
			view_range += std::abs(view_range / zoom_step);
			break;

		case GLUT_KEY_F3: // Print view information to the console.
			std::cout << "VIEW RANGE: " << view_range << std::endl;
			std::cout << "VIEW X: " << view_x << std::endl;
			std::cout << "VIEW Y: " << view_y << std::endl;
			return;

		case GLUT_KEY_F4: // Reset view.
			view_range = default_view_range;
			view_x = 0.0f;
			view_y = 0.0f;
			break;

		default: return;
		}

		update_projection(); // Update observable area.
		glutPostRedisplay();
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
