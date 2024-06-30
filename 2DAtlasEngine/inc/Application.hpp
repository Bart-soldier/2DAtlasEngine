#pragma once

#include "Constants.hpp"
#include "Timer.hpp"

#include "GraphicsEngine.hpp"
#include "PhysicsEngine.hpp"
#include "SceneManager.hpp"
#include "Ground.hpp"
#include "Character.hpp"
#include "Inventory.hpp"

#include <sstream>
#include <vector>

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
			/// <summary>The graphics engine is responsible for the creation and render of various graphical elements.
			/// <para>It also creates and handles the application's window.</para></summary>
			GraphicsEngine _graphicEngine { WIDTH, HEIGHT, "Atlas Engine 2.0" };
			/// <summary>The physics engine is responsible to move objects and check for collisions.</summary>
			PhysicsEngine _physicsEngine {};

			/* --- Utils --- */
			/// <summary>The font used throughout the program.</summary>
			TTF_Font* _font = nullptr;
			/// <summary>The timer used to count FPS.</summary>
			Timer _fpsTimer {};
			/// <summary>The timer used to cap FPS.</summary>
			Timer _fpsCapTimer {};
			/// <summary>Used to count how many frames where rendered in a second.</summary>
			int _framesCounter = 0;

			/* --- Scenes --- */
			/// <summary>Manages everything <see cref="Scene"/>-related within the game.</summary>
			SceneManager _sceneManager {};

			/* --- Players ---- */
			Character* _controlledCharacter = nullptr;
			Character* _player = nullptr;
			Character* _builder = nullptr;

			/* --- Camera --- */
			Camera _camera{ WIDTH, HEIGHT };

			/* --- UI --- */
			bool _hideUI = false;
			Inventory* _currentInventory = &_playInventory;
			Inventory _playInventory { _graphicEngine.CreateSpriteTexture("rsc/images/ui/PlayInventory.png", 1, 2), 27 };
			Inventory _buildInventory { _graphicEngine.CreateSpriteTexture("rsc/images/ui/BuildInventory.png", 1, 2), 32 };
			Texture* _minimap = nullptr;
			std::stringstream _fpsCounterText;
			Texture* _fpsCounterTexture = nullptr;

			/* --- Build Mode --- */
			GameMode _gameMode = GAMEMODE_PLAY;
			GameObject* _buildObject = nullptr;

			void Init();

			void SwitchGameMode();

			void StartFrame();
			void EndFrame();

			void CalculatePhysics();
			void RenderCurrentScene();
			void RenderCurrentCharacters();
			void RenderUI();

			float GetFPS();
			void ManuallyCapFPS();

			void HandleEvents();
			void HandleMouseMotion(int x, int y);
			void HandleMouseWheel(SDL_Event event);
			void HandleMouseButtonDown();
			void HandleKeyDownEvent(SDL_Keycode keyCode);
			void HandleKeyUpEvent(SDL_Keycode keyCode);
	};
}