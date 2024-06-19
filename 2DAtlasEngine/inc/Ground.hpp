#pragma once

#include "../inc/GameObject.hpp"

namespace Game {

	class Ground : public GameObject
	{
	public:
		Ground(AE::Texture* texture);
		~Ground();
	};
}