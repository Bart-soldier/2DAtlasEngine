#include "../inc/GameObject.hpp"

namespace Game
{
	GameObject::GameObject(AE::Texture* texture, int x, int y) : _texture{ texture }, _x{ x }, _y{ y }
	{
	}

	GameObject::~GameObject()
	{
	}

	AE::Texture* GameObject::GetTexture()
	{
		return _texture;
	}

	int GameObject::GetX()
	{
		return _x;
	}

	int GameObject::GetY()
	{
		return _y;
	}
}