#pragma once

namespace AE {
	static const int WIDTH = 640;
	static const int HEIGHT = 480;
	static const int SCREEN_FPS = 60;
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	static const int TILE_SIZE = 16;
	static const int TILE_RENDER_FACTOR = 4;

	static const bool VSYNC_ENABLED = true;
}