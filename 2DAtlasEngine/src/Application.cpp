#include "../inc/Application.hpp"

namespace AE
{
	void Application::Run()
	{
		Init();

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
		_font = nullptr;

		delete _player;
		_player = nullptr;
		delete _builder;
		_builder = nullptr;
		_controlledCharacter = nullptr;

		delete _minimap;
		_minimap = nullptr;
		delete _fpsCounterTexture;
		_fpsCounterTexture = nullptr;

		for (int i = 0; i < _buildInventory.GetCapacity(); i++) {
			if (_buildInventory.GetAt(i) != nullptr) {
				delete _buildInventory.GetAt(i);
				_buildInventory.AddAt(nullptr, i);
			}
		}
		_buildObject = nullptr;
	}

	void Application::Init()
	{
		/* --- Utils --- */
		_font = TTF_OpenFont("rsc/fonts/lazy.ttf", 28);
		if (_font == NULL)
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

		/* --- Scenes --- */
		_sceneManager.AddScene(new Scene(30, 30, "Main Scene", _graphicEngine.CreateRegularTexture("rsc/images/environments/BasicGround.png")));
		_sceneManager.SetCurrentSceneIndex(0);

		/* --- Players --- */
		_player = new Character(_graphicEngine.CreateSpriteTexture("rsc/images/characters/DrJonez.png", 4, 4), 240, 190, 6 * TILE_RENDER_SIZE);
		_player->SetBoundingBox(2 * TILE_RENDER_FACTOR, 4 * TILE_RENDER_FACTOR, TILE_RENDER_SIZE - 4 * TILE_RENDER_FACTOR, TILE_RENDER_SIZE * 2 - 4 * TILE_RENDER_FACTOR);
		_controlledCharacter = _player;
		_sceneManager.GetCurrentScene()->AddCharacter(_player);

		_builder = new Character(nullptr, _player->GetXInPixel(), _player->GetYInPixel(), _player->GetSpeed());

		/* --- Camera --- */
		_camera.FocusOn(_controlledCharacter);
		_camera.Bind(_sceneManager.GetCurrentScene()->_width * TILE_RENDER_SIZE, _sceneManager.GetCurrentScene()->_height * TILE_RENDER_SIZE);

		/* --- UI --- */
		_minimap = _graphicEngine.CreateRegularTexture("rsc/images/ui/Minimap.png");
		_minimap->SetBlendMode();
		_minimap->SetAlpha(192);

		/* --- Build Mode --- */
		_buildInventory.Add(new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/environments/Grass.png"), SceneObject::TYPE_BACKGROUND));
		_buildInventory.Add(new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/environments/Sand.png"), SceneObject::TYPE_BACKGROUND));
		_buildInventory.Add(new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/environments/Floor.png"), SceneObject::TYPE_BACKGROUND));
		_buildInventory.Add(new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/objects/Box.png"), SceneObject::TYPE_FOREGROUND));

		SceneObject* bigBox = new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/objects/BigBox.png"), SceneObject::TYPE_FOREGROUND);
		bigBox->SetBoundingBox(0, TILE_RENDER_SIZE, bigBox->GetWidth(), TILE_RENDER_SIZE);
		_buildInventory.Add(bigBox);

		SceneObject* reallyBigBox = new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/objects/ReallyBigBox.png"), SceneObject::TYPE_FOREGROUND);
		reallyBigBox->SetBoundingBox(0, TILE_RENDER_SIZE * 2, bigBox->GetWidth(), TILE_RENDER_SIZE);
		_buildInventory.Add(reallyBigBox);

		SceneObject* wideBox = new SceneObject(_graphicEngine.CreateRegularTexture("rsc/images/objects/WideBox.png"), SceneObject::TYPE_FOREGROUND);
		_buildInventory.Add(wideBox);

		_buildObject = _buildInventory.GetAtCurrentIndex();

		_fpsTimer.Start();
	}

	void Application::SwitchGameMode()
	{
		switch (_gameMode)
		{
			case GAMEMODE_PLAY:
				_gameMode = GAMEMODE_BUILD;
				_builder->SetXInPixel(_camera.GetCenterX());
				_builder->SetYInPixel(_camera.GetCenterY());
				_controlledCharacter = _builder;
				_camera.UnBind();
				_hideUI = true;
				_currentInventory = &_buildInventory;
				HandleMouseMotion();
				break;
			case GAMEMODE_BUILD:
				_gameMode = GAMEMODE_PLAY;
				_controlledCharacter = _player;
				_camera.Bind(_sceneManager.GetCurrentScene()->_width * TILE_RENDER_SIZE, _sceneManager.GetCurrentScene()->_height * TILE_RENDER_SIZE);
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
		_graphicEngine.SetViewport(GraphicsEngine::VIEWPORT_FULLSCREEN);
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
				_physicsEngine.MoveCharacters(_sceneManager.GetCurrentScene());
				break;
			case GAMEMODE_BUILD:
				_physicsEngine.MoveCharacter(_controlledCharacter, _sceneManager.GetCurrentScene());
				break;
		}

		_physicsEngine.StartDeltaTime();
	}

	void Application::RenderCurrentScene()
	{
		for (int y = 0; y < _sceneManager.GetCurrentScene()->_height; y++)
		{
			for (int x = 0; x < _sceneManager.GetCurrentScene()->_width; x++)
			{
				GameObject* gameObject = _sceneManager.GetCurrentScene()->GetBackgroundInGrid(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), gameObject->GetRenderXInPixel(), gameObject->GetRenderYInPixel(), &_camera);

				gameObject = _sceneManager.GetCurrentScene()->GetForegroundInGrid(x, y);
				if (gameObject != nullptr)
					_graphicEngine.RenderTexture(gameObject->GetTexture(), gameObject->GetRenderXInPixel(), gameObject->GetRenderYInPixel(), &_camera);
			}
		}

		if (_gameMode == GAMEMODE_BUILD && _buildObject != nullptr)
			_graphicEngine.RenderTexture(_buildObject->GetTexture(), _buildObject->GetRenderXInGrid() * TILE_RENDER_SIZE, _buildObject->GetRenderYInGrid() * TILE_RENDER_SIZE, &_camera);
	}

	void Application::RenderCurrentCharacters()
	{
		if (_gameMode == GAMEMODE_PLAY)
		{
			for (Character* character : _sceneManager.GetCurrentScene()->GetCharacters())
			{
				_graphicEngine.RenderTexture(character->GetTexture(), character->GetXInPixel(), character->GetYInPixel(), &_camera);
			}
		}
	}

	void Application::RenderUI()
	{
		if (!_hideUI) {
			_fpsCounterText.str("");
			_fpsCounterText << "FPS: " << GetFPS();
			delete _fpsCounterTexture;
			_fpsCounterTexture = _graphicEngine.CreateTextTexture(_font, _fpsCounterText.str().c_str(), { 0, 0, 0 });

			_graphicEngine.SetViewport(GraphicsEngine::VIEWPORT_FULLSCREEN);
			_graphicEngine.RenderTexture(_fpsCounterTexture, 0, 0, nullptr, GraphicsEngine::RESIZE_NONE);
			_graphicEngine.SetViewport(GraphicsEngine::VIEWPORT_MINIMAP);
			_graphicEngine.RenderTextureFullViewport(_minimap);
		}

		_graphicEngine.SetViewport(GraphicsEngine::VIEWPORT_INVENTORY);
		int drawStart = (WIDTH / 2) - (_currentInventory->GetMaxDisplayCurrentRow() / 2) * TILE_RENDER_SIZE;
		for (int i = _currentInventory->BeginCurrentRow(); i < _currentInventory->EndCurrentRow(); i++)
		{
			_currentInventory->GetTexture()->SetColumnIndex(i == _currentInventory->GetCurrentIndex());

			_graphicEngine.RenderTexture(_currentInventory->GetTexture(), drawStart, 0, nullptr);
			if(_currentInventory->GetAt(i) != nullptr)
				_graphicEngine.RenderTexture(_currentInventory->GetAt(i)->GetTexture(), drawStart, 0, nullptr, GraphicsEngine::RESIZE_THREEQUARTERS, true);
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
				HandleMouseMotion();
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

	void Application::HandleMouseMotion()
	{
		if (_gameMode == GAMEMODE_BUILD && _buildObject != nullptr)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			_buildObject->SetXInPixel(_camera.GetPosX() + x);
			_buildObject->SetYInPixel(_camera.GetPosY() + y);
		}
	}

	void Application::HandleMouseWheel(SDL_Event event)
	{
		if (event.wheel.y > 0) _currentInventory->IncrementIndex();
		else _currentInventory->DecrementIndex();

		if (_gameMode == GAMEMODE_BUILD)
		{
			_buildObject = _currentInventory->GetAtCurrentIndex();
			HandleMouseMotion();
		}
	}

	void Application::HandleMouseButtonDown()
	{
		switch (_gameMode)
		{
			case GAMEMODE_BUILD:
				if(_buildObject != nullptr)
					_sceneManager.GetCurrentScene()->SetInGrid(_buildObject->GetXInGrid(),_buildObject->GetYInGrid(),
																		 new SceneObject(*_buildObject));
		}
	}

	void Application::HandleKeyDownEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP: case SDLK_z: _controlledCharacter->StartMoving(DIRECTION_UP); break;
			case SDLK_DOWN: case SDLK_s: _controlledCharacter->StartMoving(DIRECTION_DOWN); break;
			case SDLK_LEFT: case SDLK_q: _controlledCharacter->StartMoving(DIRECTION_LEFT); break;
			case SDLK_RIGHT: case SDLK_d: _controlledCharacter->StartMoving(DIRECTION_RIGHT); break;
			case SDLK_a: _currentInventory->IncrementRow(); break;
			case SDLK_e: _currentInventory->DecrementRow(); break;
			case SDLK_TAB: SwitchGameMode(); break;
			case SDLK_ESCAPE: _graphicEngine._shouldClose = true; break;
		}
	}

	void Application::HandleKeyUpEvent(SDL_Keycode keyCode)
	{
		switch (keyCode)
		{
			case SDLK_UP: case SDLK_z: _controlledCharacter->StopMoving(DIRECTION_UP); break;
			case SDLK_DOWN: case SDLK_s: _controlledCharacter->StopMoving(DIRECTION_DOWN); break;
			case SDLK_LEFT: case SDLK_q: _controlledCharacter->StopMoving(DIRECTION_LEFT); break;
			case SDLK_RIGHT: case SDLK_d: _controlledCharacter->StopMoving(DIRECTION_RIGHT); break;
		}
	}
}