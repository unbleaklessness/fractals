#pragma once

namespace fractals_2d {

	extern float view_range;
	extern float default_view_range;

	extern float move_step;
	extern float zoom_step;

	extern float view_x;
	extern float view_y;

	extern int window_width;
	extern int window_height;

	extern void(*draw_callback)();

	void start();
}
