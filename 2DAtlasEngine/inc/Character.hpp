#pragma once

#include "../inc/GameObject.hpp"

namespace Game {

	class Character : public GameObject
	{
	public:
		Character(AE::Texture* texture, int x, int y);
		~Character();
	};
}