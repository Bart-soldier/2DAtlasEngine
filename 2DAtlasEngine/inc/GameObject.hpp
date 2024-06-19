#pragma once

#include "../inc/Texture.hpp"

namespace Game {

	class GameObject
	{
	public:
		GameObject(AE::Texture* texture);
		~GameObject();

		AE::Texture* GetTexture();

	private:
		AE::Texture* _texture;
	};
}