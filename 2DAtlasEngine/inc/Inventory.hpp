#pragma once

#include "../inc/GameObject.hpp"

#include <vector>

namespace AE
{
	class Inventory
	{
	public:
		Inventory(int capacity);
		~Inventory();

		void IncrementIndex();
		void DecrementIndex();
		int GetCurrentIndex();
		GameObject* GetAt(int index);
		GameObject* GetAtCurrentIndex();
		void Add(GameObject* item);
		int GetCapacity();

	private:
		std::vector<GameObject*> _items;
		int _capacity;
		int _spaceUsed;
		int _currentIndex;
	};
}