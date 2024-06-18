#include "../inc/AEWindow.hpp"

namespace AE {

	AEWindow::AEWindow(int width, int height, std::string name) : _width{ width }, _height{ height }, _name{ name } {
		if (!InitializeWindow()) {
			printf("Failed to initialize window!\n");
			_shouldClose = true;
			return;
		}

		if (!InitializeRenderer()) {
			printf("Failed to initialize renderer!\n");
			_shouldClose = true;
			return;
		}

		_shouldClose = false;
	}

	AEWindow::~AEWindow() {
		SDL_DestroyTexture(_frontBuffer);
		_frontBuffer = NULL;
		SDL_DestroyRenderer(_renderer);
		_renderer = NULL;

		SDL_DestroyWindow(_window);
		_window = NULL;
		
		IMG_Quit();
		SDL_Quit();
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

		return true;
	}

	bool AEWindow::InitializeRenderer() {
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
		if (_renderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		int imgFlag = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlag) & imgFlag)) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}

		return true;
	}

	SDL_Texture* AEWindow::LoadTexture(std::string path) {
		SDL_Texture* texture = NULL;
		SDL_Surface* surface = IMG_Load(path.c_str());

		if (surface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
			SDL_FreeSurface(surface);
			return NULL;
		}

		texture = SDL_CreateTextureFromSurface(_renderer, surface);
		if (texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(surface);

		return texture;
	}

	void AEWindow::ClearRenderer() {
		SDL_RenderClear(_renderer);
	}

	void AEWindow::SetViewport(Viewport viewportValue) {
		switch (viewportValue) {
			case Viewport::FULLSCREEN:
				_viewport.x = 0;
				_viewport.y = 0;
				_viewport.w = _width;
				_viewport.h = _height;
				break;
			case Viewport::MINIMAP:
				_viewport.x = _width - (_width/4);
				_viewport.y = 0;
				_viewport.w = _width / 4;
				_viewport.h = _height / 4;
				break;
		}

		SDL_RenderSetViewport(_renderer, &_viewport);
	}

	void AEWindow::DrawTexture(SDL_Texture* texture) {
		if (texture != NULL) {
			//SDL_BlitSurface(surface, NULL, _backBuffer, NULL);
			SDL_RenderCopy(_renderer, texture, NULL, NULL);
		}
	}

	void AEWindow::SwapBuffers() {
		//SDL_BlitSurface(_backBuffer, NULL, _frontBuffer, &stretchRect);
		//SDL_BlitScaled(_backBuffer, NULL, _frontBuffer, &stretchRect);
		//SDL_UpdateWindowSurface(_window);
		SDL_RenderPresent(_renderer);
	}
}