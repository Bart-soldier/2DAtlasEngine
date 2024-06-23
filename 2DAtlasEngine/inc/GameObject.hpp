#pragma once

#include "../inc/Texture.hpp"
#include "../inc/SpriteTexture.hpp"

#include <typeinfo>

namespace AE {

	class GameObject
	{
	public:
		GameObject(Texture* texture = NULL, int x = 0, int y = 0);
		~GameObject();

		SDL_Rect _boundingBox;

		Texture* GetTexture();
		int GetX();
		int GetY();

	protected:
		float _posX;
		float _posY;

	private:
		Texture* _texture;
	};
}