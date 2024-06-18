#include "../inc/Application.hpp"

namespace AE {

	void Application::Run() {
		keySurfaces[KEY_PRESS_SURFACE_DEFAULT] = _AEWindow.LoadSurface("rsc/press.png");
		keySurfaces[KEY_PRESS_SURFACE_UP] = _AEWindow.LoadSurface("rsc/up.bmp");
		keySurfaces[KEY_PRESS_SURFACE_DOWN] = _AEWindow.LoadSurface("rsc/down.bmp");
		keySurfaces[KEY_PRESS_SURFACE_LEFT] = _AEWindow.LoadSurface("rsc/left.bmp");
		keySurfaces[KEY_PRESS_SURFACE_RIGHT] = _AEWindow.LoadSurface("rsc/right.bmp");

		_AEWindow.DrawSurface(keySurfaces[KEY_PRESS_SURFACE_DEFAULT]);
		_AEWindow.SwapBuffers();

		while (!_AEWindow._shouldClose) {
			HandleEvents();

			_AEWindow.SwapBuffers();
		}
	}

	void Application::Shutdown() {
		for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
		{
			SDL_FreeSurface(keySurfaces[i]);
			keySurfaces[i] = NULL;
		}


		SDL_Quit();
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
				_AEWindow.DrawSurface(keySurfaces[KEY_PRESS_SURFACE_UP]);
				break;

			case SDLK_DOWN:
				_AEWindow.DrawSurface(keySurfaces[KEY_PRESS_SURFACE_DOWN]);
				break;

			case SDLK_LEFT:
				_AEWindow.DrawSurface(keySurfaces[KEY_PRESS_SURFACE_LEFT]);
				break;

			case SDLK_RIGHT:
				_AEWindow.DrawSurface(keySurfaces[KEY_PRESS_SURFACE_RIGHT]);
				break;

			default:
				_AEWindow.DrawSurface(keySurfaces[KEY_PRESS_SURFACE_DEFAULT]);
				break;
		}
	}
}