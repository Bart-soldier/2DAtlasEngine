#include "../inc/GameObject.hpp"

namespace AE
{
	GameObject::GameObject(Texture* texture, int x, int y) : _texture{ texture }, _posX{ static_cast<float>(x)}, _posY{ static_cast<float>(y) }
	{
		_boundingBox = { 0, 0, _texture->GetWidth() * TILE_RENDER_FACTOR, _texture->GetHeight() * TILE_RENDER_FACTOR };
	}

	GameObject::~GameObject()
	{
	}

	Texture* GameObject::GetTexture()
	{
		return _texture;
	}

	int GameObject::GetX()
	{
		return static_cast<int>(_posX);
	}

	int GameObject::GetY()
	{
		return static_cast<int>(_posY);
	}
}