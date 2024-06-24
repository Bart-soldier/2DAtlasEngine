#include "../inc/Application.hpp"

namespace AE
{
	void Application::Run()
	{
		InitializeUtils();

		std::stringstream timeText;
		Texture* text;

		Ground* grass = new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/TestGround.png"));
		_currentScene = new Scene(20, 10, "Main Scene", grass);

		Texture* minimap = _graphicEngine.CreateRegularTexture("rsc/minimap.png");
		minimap->SetBlendMode();
		minimap->SetAlpha(192);

		SpriteTexture* characterTexture = _graphicEngine.CreateSpriteTexture("rsc/images/characters/DrJonez.png", 4, 4);
		characterTexture->SetColumnIndex(0);
		_player = new Character(characterTexture, 240, 190, 2 * TILE_RENDER_SIZE);
		_player->_boundingBox = { 2 * TILE_RENDER_FACTOR, 4 * TILE_RENDER_FACTOR, TILE_RENDER_SIZE - 4 * TILE_RENDER_FACTOR, TILE_RENDER_SIZE * 2 - 4 * TILE_RENDER_FACTOR };

		//_player = new Character(_graphicEngine.CreateRegularTexture("rsc/images/environments/Sand.png"), 240, 190, 5);

		_currentScene->AddCharacter(_player);

		_overlay = new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/overlay.png"));

		while (!_graphicEngine._shouldClose)
		{
			StartFrame();

			HandleEvents();

			timeText.str("");
			timeText << "FPS: " << GetFPS();
			text = _graphicEngine.CreateTextTexture(_font, timeText.str().c_str(), { 0, 0, 0 });

			_physicsEngine.MoveCharacters(_currentScene);
			_physicsEngine._deltaTime.Start();

			RenderCurrentScene();

			_graphicEngine.RenderTexture(text, 0, 0, false);
			_graphicEngine.SetViewport(GraphicsEngine::Viewport::MINIMAP);
			_graphicEngine.RenderTextureFullViewport(minimap);

			EndFrame();
		}
	}

	void Application::Shutdown()
	{
		TTF_CloseFont(_font);
		_font = NULL;
	}

	void Application::InitializeUtils()
	{
		_font = TTF_OpenFont("rsc/fonts/lazy.ttf", 28);
		if (_font == NULL)
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

		_globalTimer.Start();
		_fpsTimer.Start();
	}

	void Application::StartFrame()
	{
		_fpsCapTimer.Start();
		_graphicEngine.ClearRenderer();
		_graphicEngine.SetViewport(GraphicsEngine::Viewport::FULLSCREEN);
	}

	void Application::EndFrame()
	{
		_graphicEngine.UpdateWindow();
		++_framesCounter;
		ManuallyCapFPS();
	}

	void Application::RenderCurrentScene() {
		for (int y = 0; y < _currentScene->_height; y++) {
			for (int x = 0; x < _currentScene->_width; x++) {
				GameObject* gameObject = _currentScene->GetBackgroundInGrid(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), x * TILE_RENDER_SIZE, y * TILE_RENDER_SIZE);

				gameObject = _currentScene->GetForegroundInGrid(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), x * TILE_RENDER_SIZE, y * TILE_RENDER_SIZE);
			}
		}

		for (Character* character : _currentScene->GetCharacters())
		{
			_graphicEngine.RenderTexture(character->GetTexture(), character->GetX(), character->GetY());
		}
	}

	void Application::RenderCurrentCharacters() {

	}

	void Application::RenderUI() {

	}

	float Application::GetFPS()
	{
		float fps = _framesCounter / (_fpsTimer.GetTicks() / 1000.f);
		return fps > 2000000 ? 0 : fps;
	}

	void Application::ManuallyCapFPS()
	{
		if (VSYNC_ENABLED) return;

		int frameTicks = _fpsCapTimer.GetTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
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
			case SDL_MOUSEMOTION:
				int x, y;
				SDL_GetMouseState(&x, &y);
				HandleMouseMotion(x, y);
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) HandleKeyDownEvent(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				if (event.key.repeat == 0) HandleKeyUpEvent(event.key.keysym.sym);
				break;
			}
		}
	}

	void Application::HandleMouseMotion(int x, int y)
	{
		_currentScene->SetForegroundInPixel(x, y, _overlay);
	}

	void Application::HandleKeyDownEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP: _player->StartMoving(UP); break;
			case SDLK_DOWN: _player->StartMoving(DOWN); break;
			case SDLK_LEFT: _player->StartMoving(LEFT); break;
			case SDLK_RIGHT: _player->StartMoving(RIGHT); break;
		}
	}

	void Application::HandleKeyUpEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP: _player->StopMoving(UP); break;
			case SDLK_DOWN: _player->StopMoving(DOWN); break;
			case SDLK_LEFT: _player->StopMoving(LEFT); break;
			case SDLK_RIGHT: _player->StopMoving(RIGHT); break;
		}
	}
}