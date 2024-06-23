#pragma once

#include "Constants.hpp"
#include "Timer.hpp"

#include "GraphicsEngine.hpp"
#include "PhysicsEngine.hpp"
#include "Scene.hpp"
#include "Ground.hpp"
#include "Character.hpp"

#include <sstream>

namespace AE {

	class Application
	{
		public:
			void Run();
			void Shutdown();

		private:
			GraphicsEngine _graphicEngine { WIDTH, HEIGHT, "Atlas Engine 2.0" };
			PhysicsEngine _physicsEngine{};
			Scene* _currentScene = NULL;
			TTF_Font* _font = NULL;
			Character* _player = NULL;

			Timer _globalTimer{};
			Timer _fpsTimer{};
			Timer _fpsCapTimer{};
			int _framesCounter = 0;

			void InitializeUtils();
			void StartFrame();
			void EndFrame();

			void RenderCurrentScene();
			void RenderCurrentCharacters();
			void RenderUI();

			float GetFPS();
			void ManuallyCapFPS();

			void HandleEvents();
			void HandleKeyDownEvent(SDL_Keycode keyCode);
			void HandleKeyUpEvent(SDL_Keycode keyCode);

			/*void HandleKeyDownEvent(SDL_Keycode keyCode);

			SDL_Texture* keyImages[KEY_PRESS_SURFACE_TOTAL];
			KeyPressSurfaces _lastSurface;*/
	};
}