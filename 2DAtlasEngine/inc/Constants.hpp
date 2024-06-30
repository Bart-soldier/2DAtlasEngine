#pragma once

namespace AE
{
	/// <summary>The window's width.</summary>
	static const int WIDTH = 1280;
	/// <summary>The window's height.</summary>
	static const int HEIGHT = 720;
	/// <summary>Flag indicating if V-Sync is enabled or not.</summary>
	static const bool VSYNC_ENABLED = true;
	/// <summary>The FPS cap if V-Sync is disabled (see <see cref="VSYNC_ENABLED"/>).</summary>
	static const int SCREEN_FPS = 60;
	/// <summary>Used to know how many ticks minimum should happen between two frames when FPS are caped (see <see cref="SCREEN_FPS"/>).</summary>
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	/// <summary>A tile's size in pixels.</summary>
	static const int TILE_SIZE = 16;
	/// <summary>A tile's render multiplicator.</summary>
	static const int TILE_RENDER_FACTOR = 4;
	/// <summary>A tile's final render size.</summary>
	static const int TILE_RENDER_SIZE = TILE_SIZE * TILE_RENDER_FACTOR;


	/// <summary>The various mouvement directions.</summary>
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_TOTAL
	};

	/// <summary>The different game modes.</summary>
	enum GameMode
	{
		GAMEMODE_PLAY,
		GAMEMODE_BUILD,
		GAMEMODE_TOTAL
	};
}