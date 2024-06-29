#include "../inc/Application.hpp"

namespace AE
{
	void Application::Run()
	{
		InitUtils();

		InitBuildMode();

		_inventoryTexture = _graphicEngine.CreateSpriteTexture("rsc/images/ui/Inventory.png", 1, 2);

		Ground* testGround = new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/TestGround.png"));
		_currentScene = new Scene(30, 30, "Main Scene", testGround);

		minimap = _graphicEngine.CreateRegularTexture("rsc/minimap.png");
		minimap->SetBlendMode();
		minimap->SetAlpha(192);

		SpriteTexture* characterTexture = _graphicEngine.CreateSpriteTexture("rsc/images/characters/DrJonez.png", 4, 4);
		characterTexture->SetColumnIndex(0);
		_player = new Character(characterTexture, 240, 190, 6 * TILE_RENDER_SIZE);
		_player->SetBoundingBox(2 * TILE_RENDER_FACTOR, 4 * TILE_RENDER_FACTOR, TILE_RENDER_SIZE - 4 * TILE_RENDER_FACTOR, TILE_RENDER_SIZE * 2 - 4 * TILE_RENDER_FACTOR);
		_controlledCharacter = _player;

		_editor = new Character(NULL, 240, 190, 6 * TILE_RENDER_SIZE);

		_camera.FocusOn(_controlledCharacter);
		_camera.Bind(_currentScene->_width * TILE_RENDER_SIZE, _currentScene->_height * TILE_RENDER_SIZE);

		_currentScene->AddCharacter(_player);

		_editObject = new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/Sand.png"));

		while (!_graphicEngine._shouldClose)
		{
			StartFrame();

			HandleEvents();

			CalculatePhysics();

			_camera.Update();
			RenderCurrentScene();
			RenderCurrentCharacters();
			RenderUI();

			EndFrame();
		}
	}

	void Application::Shutdown()
	{
		TTF_CloseFont(_font);
		_font = NULL;
	}

	void Application::InitUtils()
	{
		_font = TTF_OpenFont("rsc/fonts/lazy.ttf", 28);
		if (_font == NULL)
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

		_globalTimer.Start();
		_fpsTimer.Start();
	}

	void Application::InitBuildMode()
	{
		_buildInventory.Add(new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/Grass.png")));
		_buildInventory.Add(new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/Sand.png")));
		_buildInventory.Add(new Ground(_graphicEngine.CreateRegularTexture("rsc/images/environments/Floor.png")));
	}

	void Application::SwitchGameMode()
	{
		switch (_gameMode)
		{
			case GAMEMODE_PLAY:
				_gameMode = GAMEMODE_BUILD;
				_editor->SetXInPixel(_camera.GetCenterX());
				_editor->SetYInPixel(_camera.GetCenterY());
				_controlledCharacter = _editor;
				_camera.UnBind();
				_hideUI = true;
				_currentInventory = &_buildInventory;
				break;
			case GAMEMODE_BUILD:
				_gameMode = GAMEMODE_PLAY;
				_controlledCharacter = _player;
				_camera.Bind(_currentScene->_width * TILE_RENDER_SIZE, _currentScene->_height * TILE_RENDER_SIZE);
				_hideUI = false;
				_currentInventory = &_playInventory;
				break;
		}

		_camera.FocusOn(_controlledCharacter);
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

	void Application::CalculatePhysics()
	{
		switch (_gameMode) {
			case GAMEMODE_PLAY:
				_physicsEngine.MoveCharacters(_currentScene);
				break;
			case GAMEMODE_BUILD:
				_physicsEngine.MoveCharacter(_controlledCharacter, _currentScene);
				break;
		}

		_physicsEngine._deltaTime.Start();
	}

	void Application::RenderCurrentScene()
	{
		for (int y = 0; y < _currentScene->_height; y++)
		{
			for (int x = 0; x < _currentScene->_width; x++)
			{
				GameObject* gameObject = _currentScene->GetBackgroundInGrid(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), x * TILE_RENDER_SIZE, y * TILE_RENDER_SIZE, &_camera);

				gameObject = _currentScene->GetForegroundInGrid(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), x * TILE_RENDER_SIZE, y * TILE_RENDER_SIZE, &_camera);
			}
		}

		if (_gameMode == GAMEMODE_BUILD)
			_graphicEngine.RenderTexture(_editObject->GetTexture(), _editObject->GetXInGrid() * TILE_RENDER_SIZE, _editObject->GetYInGrid() * TILE_RENDER_SIZE, &_camera);
	}

	void Application::RenderCurrentCharacters()
	{
		if (_gameMode == GAMEMODE_PLAY)
		{
			for (Character* character : _currentScene->GetCharacters())
			{
				_graphicEngine.RenderTexture(character->GetTexture(), character->GetXInPixel(), character->GetYInPixel(), &_camera);
			}
		}
	}

	void Application::RenderUI()
	{
		if (!_hideUI) {
			timeText.str("");
			timeText << "FPS: " << GetFPS();
			text = _graphicEngine.CreateTextTexture(_font, timeText.str().c_str(), { 0, 0, 0 });

			_graphicEngine.RenderTexture(text, 0, 0, nullptr, GraphicsEngine::RESIZE_NONE);
			_graphicEngine.SetViewport(GraphicsEngine::MINIMAP);
			_graphicEngine.RenderTextureFullViewport(minimap);
		}

		_graphicEngine.SetViewport(GraphicsEngine::FULLSCREEN);
		int drawStart = (WIDTH / 2) - (_currentInventory->GetCapacity() / 2) * TILE_RENDER_SIZE;
		for (int i = 0; i < _currentInventory->GetCapacity(); i++)
		{
			if (i == _currentInventory->GetCurrentIndex()) {
				_inventoryTexture->SetColumnIndex(1);
			}
			else _inventoryTexture->SetColumnIndex(0);

			_graphicEngine.RenderTexture(_inventoryTexture, drawStart, HEIGHT - (3 * TILE_RENDER_SIZE / 2), nullptr);
			if(_currentInventory->GetAt(i) != nullptr)
				_graphicEngine.RenderTexture(_currentInventory->GetAt(i)->GetTexture(),
											 drawStart + TILE_RENDER_SIZE / 8,
											 HEIGHT - (3 * TILE_RENDER_SIZE / 2) + TILE_RENDER_SIZE / 8,
											 nullptr,
											 GraphicsEngine::RESIZE_THREEQUARTERS);
			drawStart += TILE_RENDER_SIZE;
		}
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
				break;
			case SDL_MOUSEBUTTONDOWN:
				HandleMouseButtonDown();
				break;
			case SDL_MOUSEWHEEL:
				HandleMouseWheel(event);
				break;
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
		if (_gameMode == GAMEMODE_BUILD)
		{
			_editObject->SetXInPixel(_camera.GetPosX() + x);
			_editObject->SetYInPixel(_camera.GetPosY() + y);
		}
			//_currentScene->SetForegroundInPixel(_camera.GetPosX() + x, _camera.GetPosY() + y, _overlay);
	}

	void Application::HandleMouseWheel(SDL_Event event)
	{
		if (event.wheel.y > 0) _currentInventory->IncrementIndex();
		else _currentInventory->DecrementIndex();

		if (_gameMode == GAMEMODE_BUILD)
		{
			if (_currentInventory->GetAtCurrentIndex() != nullptr)
				_editObject->SetTexture(_currentInventory->GetAtCurrentIndex()->GetTexture());
		}
	}

	void Application::HandleMouseButtonDown()
	{
		switch (_gameMode)
		{
			case GAMEMODE_BUILD:
				_currentScene->SetBackgroundInGrid(_editObject->GetXInGrid(),
												   _editObject->GetYInGrid(),
												   new Ground(_editObject->GetTexture()));
		}
	}

	void Application::HandleKeyDownEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP: case SDLK_z: _controlledCharacter->StartMoving(UP); break;
			case SDLK_DOWN: case SDLK_s: _controlledCharacter->StartMoving(DOWN); break;
			case SDLK_LEFT: case SDLK_q: _controlledCharacter->StartMoving(LEFT); break;
			case SDLK_RIGHT: case SDLK_d: _controlledCharacter->StartMoving(RIGHT); break;
			case SDLK_TAB: SwitchGameMode(); break;
			case SDLK_ESCAPE: _graphicEngine._shouldClose = true; break;
		}
	}

	void Application::HandleKeyUpEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP: case SDLK_z: _controlledCharacter->StopMoving(UP); break;
			case SDLK_DOWN: case SDLK_s: _controlledCharacter->StopMoving(DOWN); break;
			case SDLK_LEFT: case SDLK_q: _controlledCharacter->StopMoving(LEFT); break;
			case SDLK_RIGHT: case SDLK_d: _controlledCharacter->StopMoving(RIGHT); break;
		}
	}
}