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

		InitializeUtils();

		std::stringstream timeText;
		AE::Texture* text;

		AE::Texture* grassTexture = _graphicEngine.CreateTextureFromFile("rsc/images/environments/Grass.png");
		Ground* grass = new Ground(grassTexture);
		_currentScene = new Scene(40, 20, "Main Scene", grass);

		AE::Texture* minimap = _graphicEngine.CreateTextureFromFile("rsc/minimap.png");
		minimap->SetBlendMode();
		minimap->SetAlpha(192);

		AE::Texture* character = _graphicEngine.CreateTextureFromFile("rsc/images/characters/DrJonez.png");
		/*SDL_Rect spriteClips[4];
		spriteClips[0] = { 0, 64, TILE_SIZE, 2 * TILE_SIZE };
		spriteClips[1] = { TILE_SIZE, 64, TILE_SIZE, 2 * TILE_SIZE };
		spriteClips[2] = { 2 * TILE_SIZE, 64, TILE_SIZE, 2 * TILE_SIZE };
		spriteClips[3] = { 3 * TILE_SIZE, 64, TILE_SIZE, 2 * TILE_SIZE };
		int frame = 0;*/

		while (!_graphicEngine._shouldClose)
		{
			HandleEvents();

			timeText.str("");
			timeText << "Milliseconds since start time " << _globalTimer.GetTicks();
			text = _graphicEngine.CreateTextureFromText(_font, timeText.str().c_str(), { 0, 0, 0 });

			_graphicEngine.ClearRenderer();
			_graphicEngine.SetViewport(AE::GraphicsEngine::Viewport::FULLSCREEN);

			RenderCurrentScene();

			//_GraphicEngine.RenderTexture(character, 240, 190, &spriteClips[frame]);
			_graphicEngine.RenderTexture(character, 240, 190);

			_graphicEngine.RenderTexture(text);
			_graphicEngine.SetViewport(AE::GraphicsEngine::Viewport::MINIMAP);
			_graphicEngine.RenderTextureFullViewport(minimap);

			_graphicEngine.UpdateWindow();

			//frame = (frame + 1) % 4;
		}
	}

	void Application::InitializeUtils()
	{
		_font = TTF_OpenFont("rsc/fonts/lazy.ttf", 28);
		if (_font == NULL)
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

		_globalTimer.Start();
	}

	void Application::Shutdown()
	{
		TTF_CloseFont(_font);
		_font = NULL;

		/*for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
		{
			SDL_DestroyTexture(keyImages[i]);
			keyImages[i] = NULL;
		}*/
	}

	void Application::RenderCurrentScene() {
		for (int y = 0; y < _currentScene->_height; y++) {
			for (int x = 0; x < _currentScene->_width; x++) {
				GameObject* gameObject = _currentScene->GetForeground(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), x * TILE_SIZE, y * TILE_SIZE);

				gameObject = _currentScene->GetBackground(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), x * TILE_SIZE, y * TILE_SIZE);
			}
		}
	}

	void Application::RenderCurrentCharacters() {

	}

	void Application::RenderUI() {

	}

	void Application::HandleEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type) {
				case SDL_QUIT:
					_graphicEngine._shouldClose = true;
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