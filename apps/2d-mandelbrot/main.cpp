#ifdef _WIN32
	#include <windows.h>
#endif
#include <GL/glut.h>
#include <complex>
#include <iostream>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

// Mandelbrot set domain is within the circle bounded by square with side length of 2:
const float mandelbrot_range = 2.0f;

// Find the radius of this circle:
const float mandelbrot_radius = std::sqrt(powf(mandelbrot_range, 2.0f) + powf(mandelbrot_range, 2.0f));

// Observable area of the Mandelbrot set. By default, it is the whole set. We can zoom in/out:
float view_range = mandelbrot_range;
//float view_range = 0.0333709f;

// Location of the observable area. We can move left/right, top/bottom:
float view_x = 0.42884f;
float view_y = -0.231345f;

/*
 * List of nice observable areas:
 * |   RANGE   |     X     |     Y     |
 * | 0.0222473 | 0.42884   | -0.231345 |
 * | 0.0333709 | 0.42884   | -0.231345 |
 */

// Step sizes for zooming and moving the observable area:
const float move_step = 10.0f;
const float zoom_step = 2.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Divide observable area into grid.
    // We then can use grid points as input points for Mandelbrot set formula.
    const float step = (mandelbrot_range / 1500.0f) * view_range; // Grid width/height.
    const float jumps = 40.0f / view_range; // Number of times to check each point.

    // Mandelbrot set formula: z_(n + 1) = z_n^2 + c.
    std::complex<float> z;
    std::complex<float> c;

    glPointSize(1.5f);
    glBegin(GL_POINTS);
    // Iterate through divided observable area (X and Y coordinates applied):
    for (float i = -view_range + view_x; i <= view_range + view_x; i += step)
    {
        for (float j = -view_range + view_y; j <= view_range + view_y; j += step)
        {
            // Pick a point:
            z = {0, 0};
            c = {i, j};
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
            view_range = mandelbrot_range;
            view_x = 0.0f;
            view_y = 0.0f;
            break;

        default: return;
    }

    update_projection(); // Update observable area.
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Mandelbrot Set");

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}