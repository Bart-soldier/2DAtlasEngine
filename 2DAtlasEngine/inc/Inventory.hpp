#pragma once

#include "../inc/GameObject.hpp"

#include <vector>

namespace AE
{
	class Inventory
	{
	public:
		Inventory(SpriteTexture* texture, int capacity);
		~Inventory();

		void IncrementIndex();
		void DecrementIndex();
		void AddAt(GameObject* item, int index);
		void Add(GameObject* item);

		SpriteTexture* GetTexture();
		int GetCapacity();
		int GetCurrentIndex();
		GameObject* GetAt(int index);
		GameObject* GetAtCurrentIndex();

	private:
		SpriteTexture* _texture;
		std::vector<GameObject*> _items;
		int _capacity;
		int _spaceUsed;
		int _currentIndex;
	};
}