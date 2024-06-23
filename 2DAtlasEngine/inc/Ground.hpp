#pragma once

#include "../inc/GameObject.hpp"

namespace AE {

	class Ground : public GameObject
	{
	public:
		Ground(Texture* texture);
		~Ground();
	};
}