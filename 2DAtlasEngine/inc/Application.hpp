#pragma once

#include "Constants.hpp"
#include "Timer.hpp"

#include "GraphicsEngine.hpp"
#include "PhysicsEngine.hpp"
#include "Scene.hpp"
#include "Ground.hpp"
#include "Character.hpp"

#include <sstream>

namespace AE
{
	/// <summary>The application controls the overall behavior of the program.</summary>
	class Application
	{
		public:
			/// <summary>Initializes the applications and initiates the game loop.</summary>
			void Run();
			/// <summary>Closes the application and destroys its content.</summary>
			void Shutdown();

		private:
			GraphicsEngine _graphicEngine { WIDTH, HEIGHT, "Atlas Engine 2.0" };
			PhysicsEngine _physicsEngine{};
			Scene* _currentScene = NULL;
			TTF_Font* _font = NULL;
			Character* _player = NULL;
			Ground* _overlay = NULL;

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
			void HandleMouseMotion(int x, int y);
			void HandleKeyDownEvent(SDL_Keycode keyCode);
			void HandleKeyUpEvent(SDL_Keycode keyCode);
	};
}