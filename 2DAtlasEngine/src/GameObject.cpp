#include "../inc/GameObject.hpp"

namespace Game
{
	GameObject::GameObject(AE::Texture* texture) : _texture{ texture }
	{
	}

	GameObject::~GameObject()
	{
	}

	AE::Texture* GameObject::GetTexture()
	{
		return _texture;
	}
}