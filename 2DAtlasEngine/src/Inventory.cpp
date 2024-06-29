#include "../inc/Inventory.hpp"

namespace AE
{
	Inventory::Inventory(int capacity) : _capacity { capacity }
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

	void Inventory::Add(GameObject* item)
	{
		_items[_spaceUsed++] = item;
	}

	int Inventory::GetCapacity()
	{
		return _capacity;
	}
}