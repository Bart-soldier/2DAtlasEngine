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
			static constexpr int WIDTH = 640;
			static constexpr int HEIGHT = 480;
			static constexpr int TILE_SIZE = 16;

			void Run();
			void Shutdown();

		private:
			AE::GraphicsEngine _graphicEngine { WIDTH, HEIGHT, "Atlas Engine 2.0" };
			AE::Timer _globalTimer {};
			Scene* _currentScene = NULL;
			TTF_Font* _font = NULL;

			void InitializeUtils();

			void RenderCurrentScene();
			void RenderCurrentCharacters();
			void RenderUI();

			void HandleEvents();
			/*void HandleKeyDownEvent(SDL_Keycode keyCode);

			SDL_Texture* keyImages[KEY_PRESS_SURFACE_TOTAL];
			KeyPressSurfaces _lastSurface;*/
	};
}