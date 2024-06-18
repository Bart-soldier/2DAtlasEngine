#pragma once

#include "GraphicsEngine.hpp"

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

			void Run();
			void Shutdown();

		private:
			AE::GraphicsEngine _GraphicEngine{ WIDTH, HEIGHT, "Atlas Engine 2.0" };

			void HandleEvents();
			/*void HandleKeyDownEvent(SDL_Keycode keyCode);

			SDL_Texture* keyImages[KEY_PRESS_SURFACE_TOTAL];
			KeyPressSurfaces _lastSurface;*/
	};
}