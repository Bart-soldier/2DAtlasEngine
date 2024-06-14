#include "../inc/Application.hpp"

namespace AE {

	void Application::run() {
		SDL_Event event;

		if(!_AEWindow.LoadImage())
			printf("Failed to load media!\n");

		_AEWindow.DisplayImage();

		while (!_AEWindow.shouldClose(&event)) {
			SDL_PollEvent(&event);
		}
	}

	void Application::shutdown() {
		SDL_Quit();
	}
}