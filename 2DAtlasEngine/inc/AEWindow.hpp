#pragma once

#include <SDL.h>
#include <string>

namespace AE {

	class AEWindow {

	public:
		AEWindow(int width, int height, std::string name);
		~AEWindow();

		AEWindow(const AEWindow&) = delete;
		AEWindow& operator=(const AEWindow&) = delete;

		bool shouldClose(SDL_Event* event);
		bool LoadImage();
		void DisplayImage();

	private:
		SDL_Window* _window;
		SDL_Surface* _screenSurface;
		SDL_Surface* _image;
		std::string _name;
		const int _width;
		const int _height;

		bool InitializeWindow();
	};
}