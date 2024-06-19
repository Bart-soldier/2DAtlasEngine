#include "../inc/Application.hpp"

namespace Game
{
	void Application::Run()
	{
		/*keyImages[KEY_PRESS_SURFACE_DEFAULT] = _AEWindow.LoadTexture("rsc/press.png");
		keyImages[KEY_PRESS_SURFACE_UP] = _AEWindow.LoadTexture("rsc/up.bmp");
		keyImages[KEY_PRESS_SURFACE_DOWN] = _AEWindow.LoadTexture("rsc/down.bmp");
		keyImages[KEY_PRESS_SURFACE_LEFT] = _AEWindow.LoadTexture("rsc/left.bmp");
		keyImages[KEY_PRESS_SURFACE_RIGHT] = _AEWindow.LoadTexture("rsc/right.bmp");*/

		AE::Texture* minimap = _GraphicEngine.LoadTextureFromFile("rsc/minimap.png");
		AE::Texture* character = _GraphicEngine.LoadTextureFromFile("rsc/images/characters/DrJonez.png", true);
		SDL_Rect clip = { 0, 64, TILE_WIDTH, 2 * TILE_HEIGHT };
		AE::Texture* background = _GraphicEngine.LoadTextureFromFile("rsc/background.png");

		//_lastSurface = KEY_PRESS_SURFACE_DEFAULT;

		while (!_GraphicEngine._shouldClose)
		{
			HandleEvents();

			_GraphicEngine.ClearRenderer();
			_GraphicEngine.SetViewport(AE::GraphicsEngine::Viewport::FULLSCREEN);
			_GraphicEngine.RenderTexture(background);
			_GraphicEngine.RenderTexture(character, 240, 190, &clip);
			_GraphicEngine.SetViewport(AE::GraphicsEngine::Viewport::MINIMAP);
			_GraphicEngine.RenderTextureFullViewport(minimap);
			_GraphicEngine.UpdateWindow();
		}
	}

	void Application::Shutdown()
	{
		/*for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
		{
			SDL_DestroyTexture(keyImages[i]);
			keyImages[i] = NULL;
		}*/
	}

	void Application::HandleEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type) {
				case SDL_QUIT:
					_GraphicEngine._shouldClose = true;
					return;
				/*case SDL_KEYDOWN:
					HandleKeyDownEvent(event.key.keysym.sym);
					break;
				}*/
			}
		}
	}

	/*void Application::HandleKeyDownEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP:
				_lastSurface = KEY_PRESS_SURFACE_UP;
				break;

			case SDLK_DOWN:
				_lastSurface = KEY_PRESS_SURFACE_DOWN;
				break;

			case SDLK_LEFT:
				_lastSurface = KEY_PRESS_SURFACE_LEFT;
				break;

			case SDLK_RIGHT:
				_lastSurface = KEY_PRESS_SURFACE_RIGHT;
				break;

			default:
				_lastSurface = KEY_PRESS_SURFACE_DEFAULT;
				break;
		}
	}*/
}