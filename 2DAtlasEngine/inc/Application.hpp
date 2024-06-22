#pragma once

#include "Timer.hpp"

#include "GraphicsEngine.hpp"
#include "Scene.hpp"
#include "Ground.hpp"

#include <sstream>

namespace Game {

	class Application
	{
		/*enum KeyPressSurfaces
		{
			KEY_PRESS_SURFACE_DEFAULT,
			KEY_PRESS_SURFACE_UP,
			KEY_PRESS_SURFACE_DOWN,
			KEY_PRESS_SURFACE_LEFT,
			KEY_PRESS_SURFACE_RIGHT,
			KEY_PRESS_SURFACE_TOTAL
		};*/

		public:
			static const int WIDTH = 640;
			static const int HEIGHT = 480;
			static const int SCREEN_FPS = 60;
			static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
			static const int TILE_SIZE = 16;

			static const bool VSYNC_ENABLED = false;

			void Run();
			void Shutdown();

		private:
			AE::GraphicsEngine _graphicEngine { WIDTH, HEIGHT, "Atlas Engine 2.0", VSYNC_ENABLED };
			AE::Timer _globalTimer {};
			AE::Timer _fpsTimer {};
			AE::Timer _fpsCapTimer {};
			int _framesCounter = 0;
			Scene* _currentScene = NULL;
			TTF_Font* _font = NULL;

			void InitializeUtils();

			void RenderCurrentScene();
			void RenderCurrentCharacters();
			void RenderUI();

			void HandleEvents();

			float GetFPS();
			void ManuallyCapFPS();

			/*void HandleKeyDownEvent(SDL_Keycode keyCode);

			SDL_Texture* keyImages[KEY_PRESS_SURFACE_TOTAL];
			KeyPressSurfaces _lastSurface;*/
	};
}