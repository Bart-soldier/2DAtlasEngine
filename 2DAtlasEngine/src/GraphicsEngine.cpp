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

		if (!InitializeLibraries())
		{
			printf("Failed to initialize librairies!\n");
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
		
		TTF_Quit();
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

	bool GraphicsEngine::InitializeRenderer()
	{
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		return true;
	}

	bool GraphicsEngine::InitializeLibraries()
	{
		int imgFlag = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlag) & imgFlag)) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}

		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			return false;
		}

		return true;
	}

	void GraphicsEngine::ClearRenderer()
	{
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(_renderer);
	}

	void GraphicsEngine::SetViewport(Viewport viewportValue)
	{
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

	void GraphicsEngine::UpdateWindow()
	{
		SDL_RenderPresent(_renderer);
	}

	Texture* GraphicsEngine::CreateTextureFromFile(std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
	{
		return new Texture(_renderer, path, colorKeyed, kred, kgreen, kblue);
	}

	Texture* GraphicsEngine::CreateTextureFromText(TTF_Font* font, std::string text, SDL_Color color)
	{
		return new Texture(_renderer, font, text, color);
	}

	void GraphicsEngine::RenderTexture(Texture* texture, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		if (texture != NULL)
		{
			SDL_Rect renderQuad = { x, y, texture->GetWidth(), texture->GetHeight()};

			if (clip != NULL)
			{
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}

			SDL_RenderCopyEx(_renderer, texture->GetTexture(), clip, &renderQuad, angle, center, flip);
		}
	}

	void GraphicsEngine::RenderTextureFullViewport(Texture* texture)
	{
		if (texture != NULL)
		{
			SDL_Rect renderQuad = { 0, 0, _viewport.w, _viewport.h };
			SDL_RenderCopy(_renderer, texture->GetTexture(), NULL, &renderQuad);
		}
	}
}