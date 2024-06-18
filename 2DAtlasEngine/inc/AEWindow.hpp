#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace AE {

	class AEWindow {

	public:
		AEWindow(int width, int height, std::string name);
		~AEWindow();

		AEWindow(const AEWindow&) = delete;
		AEWindow& operator=(const AEWindow&) = delete;

		bool _shouldClose;

		SDL_Texture* LoadTexture(std::string path);
		void ClearRenderer();
		void DrawTexture(SDL_Texture* texture);
		void SwapBuffers();

	private:
		SDL_Window* _window;
		std::string _name;
		const int _width;
		const int _height;

		SDL_Renderer* _renderer;
		SDL_Texture* _frontBuffer;

		bool InitializeWindow();
		bool InitializeRenderer();
	};
}