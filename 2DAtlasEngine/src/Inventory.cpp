#include "../inc/Inventory.hpp"

namespace AE
{
	Inventory::Inventory(SpriteTexture* texture, int capacity) : _texture{ texture }, _capacity { capacity }
	{
		_items = std::vector<GameObject*>(_capacity, nullptr);
		_spaceUsed = 0;
		_currentIndex = 0;
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::IncrementIndex()
	{
		++_currentIndex %= _capacity;
	}

	void Inventory::DecrementIndex()
	{
		_currentIndex = --_currentIndex < 0 ? _capacity - 1 : _currentIndex;
	}

	void Inventory::AddAt(GameObject* item, int index)
	{
		if(index >= 0 && index < _capacity)
		{
			_items[index] = item;
		}
	}

	void Inventory::Add(GameObject* item)
	{
		_items[_spaceUsed++] = item;
	}

	SpriteTexture* Inventory::GetTexture()
	{
		return _texture;
	}

	int Inventory::GetCapacity()
	{
		return _capacity;
	}

	int Inventory::GetCurrentIndex()
	{
		return _currentIndex;
	}

	GameObject* Inventory::GetAt(int index)
	{
		return (index >= 0 && index < _capacity) ? _items.at(index) : nullptr;
	}

	GameObject* Inventory::GetAtCurrentIndex()
	{
		return (_currentIndex >= 0 && _currentIndex < _capacity) ? _items.at(_currentIndex) : nullptr;
	}
}