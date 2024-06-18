#include "../inc/GraphicsEngine.hpp"

namespace AE
{
	GraphicsEngine::GraphicsEngine(int width, int height, std::string name) : _width{ width }, _height{ height }, _name{ name }
	{
		if (!InitializeWindow())
		{
			printf("Failed to initialize window!\n");
			_shouldClose = true;
			return;
		}

		if (!InitializeRenderer())
		{
			printf("Failed to initialize renderer!\n");
			_shouldClose = true;
			return;
		}

		_shouldClose = false;
	}

	GraphicsEngine::~GraphicsEngine()
	{
		SDL_DestroyRenderer(_renderer);
		_renderer = NULL;
		SDL_DestroyWindow(_window);
		_window = NULL;
		
		IMG_Quit();
		SDL_Quit();
	}

	bool GraphicsEngine::InitializeWindow()
	{
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

	bool GraphicsEngine::InitializeRenderer() {
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

	void GraphicsEngine::ClearRenderer() {
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(_renderer);
	}

	void GraphicsEngine::SetViewport(Viewport viewportValue) {
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

	void GraphicsEngine::UpdateWindow() {
		SDL_RenderPresent(_renderer);
	}

	Texture* GraphicsEngine::LoadTextureFromFile(std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue) {
		return new Texture(_renderer, path, colorKeyed, kred, kgreen, kblue);
	}

	void GraphicsEngine::RenderTexture(Texture* texture, int x, int y, int width, int height) {
		if (texture != NULL) {
			SDL_Rect renderQuad = { x, y,
									width  == -1 ? texture->GetWidth()  : width,
									height == -1 ? texture->GetHeight() : height};
			SDL_RenderCopy(_renderer, texture->GetTexture(), NULL, &renderQuad);
		}
	}

	void GraphicsEngine::RenderTextureFullViewport(Texture* texture) {
		if (texture != NULL) {
			SDL_Rect renderQuad = { 0, 0, _viewport.w, _viewport.h };
			SDL_RenderCopy(_renderer, texture->GetTexture(), NULL, &renderQuad);
		}
	}
}