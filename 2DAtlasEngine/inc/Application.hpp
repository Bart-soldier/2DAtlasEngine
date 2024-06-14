#pragma once

#include "AEWindow.hpp"

namespace AE {

	class Application {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();
		void shutdown();

	private:
		AEWindow _AEWindow{ WIDTH, HEIGHT, "Atlas Engine 2.0" };
	};
}