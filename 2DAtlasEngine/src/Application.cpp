#include "../inc/Application.hpp"

namespace AE {

	void Application::Run() {
		keyImages[KEY_PRESS_SURFACE_DEFAULT] = _AEWindow.LoadTexture("rsc/press.png");
		keyImages[KEY_PRESS_SURFACE_UP] = _AEWindow.LoadTexture("rsc/up.bmp");
		keyImages[KEY_PRESS_SURFACE_DOWN] = _AEWindow.LoadTexture("rsc/down.bmp");
		keyImages[KEY_PRESS_SURFACE_LEFT] = _AEWindow.LoadTexture("rsc/left.bmp");
		keyImages[KEY_PRESS_SURFACE_RIGHT] = _AEWindow.LoadTexture("rsc/right.bmp");

		SDL_Texture* minimap = _AEWindow.LoadTexture("rsc/minimap.png");

		_lastSurface = KEY_PRESS_SURFACE_DEFAULT;

		while (!_AEWindow._shouldClose) {
			HandleEvents();

			_AEWindow.ClearRenderer();
			_AEWindow.SetViewport(AEWindow::Viewport::FULLSCREEN);
			_AEWindow.DrawTexture(keyImages[_lastSurface]);
			_AEWindow.SetViewport(AEWindow::Viewport::MINIMAP);
			_AEWindow.DrawTexture(minimap);
			_AEWindow.SwapBuffers();
		}

		SDL_DestroyTexture(minimap);
	}

	void Application::Shutdown() {
		for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
		{
			SDL_DestroyTexture(keyImages[i]);
			keyImages[i] = NULL;
		}
	}

	void Application::HandleEvents() {
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				_AEWindow._shouldClose = true;
				return;
			case SDL_KEYDOWN:
				HandleKeyDownEvent(event.key.keysym.sym);
				break;
			}
		}
	}

	void Application::HandleKeyDownEvent(SDL_Keycode keyCode) {
		switch (keyCode) {
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
	}
}