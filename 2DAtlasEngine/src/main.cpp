#include "../inc/Application.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, char* args[])
{
	Game::Application _application{};

	try
	{
		_application.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	_application.Shutdown();

	return EXIT_SUCCESS;
}