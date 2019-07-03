#include "fractals-3d/fractals_3d.h"

#include <GL/glut.h>

namespace fractals_3d {

	int window_width = 800;
	int window_height = 800;

	void draw() {

	}

	void(*draw_callback)() = &draw;
}

int main(int argc, char **argv) {

	fractals_3d::start();

	return 0;
}