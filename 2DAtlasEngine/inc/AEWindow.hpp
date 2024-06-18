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

		SDL_Surface* LoadSurface(std::string path);
		bool DrawSurface(SDL_Surface* surface);
		void SwapBuffers();

	private:
		SDL_Window* _window;
		SDL_Surface* _frontBuffer;
		SDL_Surface* _backBuffer;
		std::string _name;
		const int _width;
		const int _height;
		SDL_Rect stretchRect;

		bool InitializeWindow();
	};
}