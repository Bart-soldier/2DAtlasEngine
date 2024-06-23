#pragma once

namespace AE {
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	static const int SCREEN_FPS = 60;
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	static const int TILE_SIZE = 16;
	static const int TILE_RENDER_FACTOR = 2;
	static const int TILE_RENDER_SIZE = TILE_SIZE * TILE_RENDER_FACTOR;

	static const bool VSYNC_ENABLED = true;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
}