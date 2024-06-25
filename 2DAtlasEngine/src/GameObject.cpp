#include "../inc/GameObject.hpp"

namespace AE
{
	GameObject::GameObject(Texture* texture, int x, int y) : _texture{ texture }, _posX{ static_cast<float>(x)}, _posY{ static_cast<float>(y) }
	{
		if(_texture != NULL)
			_boundingBox = { 0, 0, _texture->GetWidth() * TILE_RENDER_FACTOR, _texture->GetHeight() * TILE_RENDER_FACTOR };
		else
			_boundingBox = { 0, 0, 0, 0 };
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::SetBoundingBox(int x, int y, int width, int height)
	{
		_boundingBox = { x, y, width, height };
	}

	void GameObject::SetX(int x)
	{
		_posX = x;
	}

	void GameObject::SetY(int y)
	{
		_posY = y;
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

	int GameObject::GetWidth()
	{
		return _boundingBox.w;
	}

	int GameObject::GetHeight()
	{
		return _boundingBox.h;
	}

	SDL_Rect GameObject::GetBoundingBox()
	{
		return _boundingBox;
	}
}