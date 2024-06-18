#include "../inc/AEWindow.hpp"

namespace AE {

	AEWindow::AEWindow(int width, int height, std::string name) : _width{ width }, _height{ height }, _name{ name } {
		if(!InitializeWindow())
			printf("Failed to initialize!\n");

		_shouldClose = false;

		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = _width;
		stretchRect.h = _height;
	}

	AEWindow::~AEWindow() {
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	bool AEWindow::InitializeWindow() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return false;
		}

		_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
		if (_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		
		_frontBuffer = SDL_GetWindowSurface(_window);
		return true;
	}

	SDL_Surface* AEWindow::LoadSurface(std::string path) {
		SDL_Surface* optimizedSurface = NULL;
		SDL_Surface* surface = SDL_LoadBMP(path.c_str());

		if (surface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			return NULL;
		}

		optimizedSurface = SDL_ConvertSurface(surface, _frontBuffer->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(surface);

		return optimizedSurface;
	}

	bool AEWindow::DrawSurface(SDL_Surface* surface) {
		if (surface != NULL) {
			//SDL_BlitSurface(surface, NULL, _backBuffer, NULL);
			_backBuffer = surface;
			return true;
		}

		return false;
	}

	void AEWindow::SwapBuffers() {
		//SDL_BlitSurface(_backBuffer, NULL, _frontBuffer, &stretchRect);
		SDL_BlitScaled(_backBuffer, NULL, _frontBuffer, &stretchRect);
		SDL_UpdateWindowSurface(_window);
	}
}