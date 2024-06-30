#include "../inc/GameObject.hpp"

namespace AE
{
	GameObject::GameObject(Texture* texture, int x, int y) : _texture{ texture }, _posX{ static_cast<float>(x)}, _posY{ static_cast<float>(y) }
	{
		SetDimensions();
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::SetDimensions()
	{
		if (_texture != nullptr)
			_boundingBox = { 0, 0, _texture->GetWidth() * TILE_RENDER_FACTOR, _texture->GetHeight() * TILE_RENDER_FACTOR };
		else
			_boundingBox = { 0, 0, 0, 0 };

		_width = _boundingBox.w;
		_height = _boundingBox.h;
	}

	void GameObject::SetBoundingBox(int x, int y, int width, int height)
	{
		_boundingBox = { x, y, width, height };
	}

	void GameObject::SetXInPixel(int x)
	{
		_posX = x;
	}

	void GameObject::SetYInPixel(int y)
	{
		_posY = y;
	}

	void GameObject::SetTexture(Texture* texture)
	{
		if (texture != nullptr)
		{
			_texture = texture;
			SetDimensions();
		}
	}

	Texture* GameObject::GetTexture()
	{
		return _texture;
	}

	int GameObject::GetXInPixel()
	{
		return static_cast<int>(_posX);
	}

	int GameObject::GetYInPixel()
	{
		return static_cast<int>(_posY);
	}

	int GameObject::GetXInGrid()
	{
		int x = static_cast<int>(_posX);
		return x < 0 ? (x / TILE_RENDER_SIZE) - 1 : x / TILE_RENDER_SIZE;
	}

	int GameObject::GetYInGrid()
	{
		int y = static_cast<int>(_posY);
		return y < 0 ? (y / TILE_RENDER_SIZE) - 1 : y / TILE_RENDER_SIZE;
	}

	int GameObject::GetWidth()
	{
		return _width;
	}

	int GameObject::GetHeight()
	{
		return _height;
	}

	SDL_Rect GameObject::GetBoundingBox()
	{
		return _boundingBox;
	}
}