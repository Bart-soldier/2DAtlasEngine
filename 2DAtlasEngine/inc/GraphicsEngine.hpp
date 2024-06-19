#pragma once

#include "../inc/Texture.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace AE
{
	class GraphicsEngine
	{
	public:
		enum Viewport
		{
			FULLSCREEN,
			MINIMAP,
			TOTAL
		};

		GraphicsEngine(int width, int height, std::string name);
		~GraphicsEngine();

		GraphicsEngine(const GraphicsEngine&) = delete;
		GraphicsEngine& operator=(const GraphicsEngine&) = delete;

		bool _shouldClose;

		void ClearRenderer();
		void SetViewport(Viewport viewportValue);
		void UpdateWindow();

		Texture* LoadTextureFromFile(std::string path, bool colorKeyed = false, Uint8 kred = 0, Uint8 kgreen = 0xFF, Uint8 kblue = 0xFF);
		void RenderTexture(Texture* texture, int x = 0, int y = 0, SDL_Rect* clip = NULL);
		void RenderTextureFullViewport(Texture* texture);

	private:
		SDL_Window* _window;
		std::string _name;
		const int _width;
		const int _height;

		SDL_Renderer* _renderer;
		SDL_Rect _viewport;

		bool InitializeWindow();
		bool InitializeRenderer();
	};
}