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

	private:
		SDL_Window* window;
		SDL_Surface* screenSurface;
		std::string _name;
		const int _width;
		const int _height;

		void InitializeWindow();
	};
}