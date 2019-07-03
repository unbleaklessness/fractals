#pragma once

namespace fractals_3d {

	extern int window_width;
	extern int window_height;

	extern void(*draw_callback)();

	void start();
}