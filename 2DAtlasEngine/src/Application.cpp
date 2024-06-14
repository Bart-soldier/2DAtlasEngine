#include "../inc/Application.hpp"

namespace AE {

	void Application::run() {
		SDL_Event event;

		while (!_AEWindow.shouldClose(&event)) {
			SDL_PollEvent(&event);
		}
	}
}