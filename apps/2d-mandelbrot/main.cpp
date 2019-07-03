#include "fractals-2d/fractals_2d.h"

#include <GL/glut.h>

#include <cmath>
#include <complex>

/*
 * List of nice observable areas:
 * |   RANGE   |     X     |     Y     |
 * | 0.0222473 | 0.42884   | -0.231345 |
 * | 0.0333709 | 0.42884   | -0.231345 |
 */

namespace fractals_2d {

	// Observable area of the Mandelbrot set. By default, it is the whole set. We can zoom in/out:
	float view_range = 2.0f;
	float default_view_range = view_range;

	float move_step = 10.0f;
	float zoom_step = 2.0f;

	float view_x = 0.42884f;
	float view_y = -0.231345f;

	int window_width = 800;
	int window_height = 800;

	void draw() {
		// Divide observable area into grid.
			// We then can use grid points as input points for Mandelbrot set formula.
		const float step = (default_view_range / 1500.0f) * view_range; // Grid width/height.
		const float jumps = 40.0f / view_range; // Number of times to check each point.

		// Mandelbrot set formula: z_(n + 1) = z_n^2 + c.
		std::complex<float> z;
		std::complex<float> c;

		const float mandelbrot_radius = std::sqrt(powf(default_view_range, 2.0f) + powf(default_view_range, 2.0f));

		glPointSize(1.5f);
		glBegin(GL_POINTS);
		// Iterate through divided observable area (X and Y coordinates applied):
		for (float i = -view_range + view_x; i <= view_range + view_x; i += step)
		{
			for (float j = -view_range + view_y; j <= view_range + view_y; j += step)
			{
				// Pick a point:
				z = { 0, 0 };
				c = { i, j };
				// Check this point:
				for (float k = 1; k <= jumps; k++)
				{
					z = (z * z) + c; // Make next `jump`.
					if (std::abs(z) > mandelbrot_radius) // This point is not in Mandelbrot set (it left the domain).
					{
						// Color this point by how many `jumps` it takes to leave Mandelbrot set domain:
						glColor3f(k / jumps / view_range, 0.0f, 0.0f);
						glVertex2f(c.real(), c.imag());
						break;
					}
					if (k == jumps) // This point is in Mandelbrot set.
					{
						// Color this point completely red:
						glColor3f(1.0f, 0.0f, 0.0f);
						glVertex2f(c.real(), c.imag());
						break;
					}
				}
			}
		}
		glEnd();
	}

	void(*draw_callback)() = &draw;
}

int main(int argc, char **argv)
{
	fractals_2d::start();

    return 0;
}