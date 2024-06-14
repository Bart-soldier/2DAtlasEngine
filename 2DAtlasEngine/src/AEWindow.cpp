#include "../inc/AEWindow.hpp"

namespace AE {

	AEWindow::AEWindow(int width, int height, std::string name) : _width{ width }, _height{ height }, _name{ name } {
		if(!InitializeWindow())
			printf("Failed to initialize!\n");
	}

	AEWindow::~AEWindow() {
		SDL_FreeSurface(_image);
		_image = NULL;
		SDL_FreeSurface(_screenSurface);
		_screenSurface = NULL;
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	bool AEWindow::shouldClose(SDL_Event* event) {
		return event->type == SDL_QUIT ? true : false;
	}

	bool AEWindow::InitializeWindow() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
			if (_window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				_screenSurface = SDL_GetWindowSurface(_window);
			}
		}
	}

	bool AEWindow::LoadImage() {
		_image = SDL_LoadBMP("rsc/hello_world.bmp");
		if (_image == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
			return false;
		}

		return true;
	}

	void AEWindow::DisplayImage() {
		if (_image != NULL) {
			SDL_BlitSurface(_image, NULL, _screenSurface, NULL);
			SDL_UpdateWindowSurface(_window);
		}
			
	}
}