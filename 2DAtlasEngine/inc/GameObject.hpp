#pragma once

#include "../inc/Texture.hpp"

namespace Game {

	class GameObject
	{
	public:
		GameObject(AE::Texture* texture = NULL, int x = 0, int y = 0);
		~GameObject();

		AE::Texture* GetTexture();
		int GetX();
		int GetY();

	private:
		AE::Texture* _texture;
		int _x;
		int _y;
	};
}