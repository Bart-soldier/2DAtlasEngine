#include "../inc/Inventory.hpp"

namespace AE
{
	Inventory::Inventory(SpriteTexture* texture, int capacity) : _texture{ texture }, _capacity { capacity }
	{
		_items = std::vector<GameObject*>(_capacity, nullptr);
		_spaceUsed = 0;
		_currentIndex = 0;

		_maxDisplayWidth = (WIDTH - 4 * TILE_RENDER_SIZE) / TILE_RENDER_SIZE;
		_rowNb = _capacity % _maxDisplayWidth == 0 ? (_capacity / _maxDisplayWidth) : (_capacity / _maxDisplayWidth) + 1;
		_currentRow = 0;
		UpdateMaxDisplayCurrentRow();
	}

	Inventory::~Inventory()
	{
		delete _texture;
		_texture = nullptr;
	}

	void Inventory::IncrementIndex()
	{
		_currentIndex = ++_currentIndex >= EndCurrentRow() ? BeginCurrentRow() : _currentIndex;
	}

	void Inventory::DecrementIndex()
	{
		_currentIndex = --_currentIndex < BeginCurrentRow() ? EndCurrentRow() - 1 : _currentIndex;
	}

	bool Inventory::AddAt(GameObject* item, int index)
	{
		if(index >= 0 && index < _capacity)
		{
			_items[index] = item;
			return true;
		}

		return false;
	}

	bool Inventory::Add(GameObject* item)
	{
		if (_spaceUsed >= _capacity) return false;

		_items[_spaceUsed++] = item;
		return true;
	}

	void Inventory::IncrementRow()
	{
		++_currentRow %= _rowNb;
		UpdateMaxDisplayCurrentRow();
	}

	void Inventory::DecrementRow()
	{
		_currentRow = --_currentRow < 0 ? _rowNb - 1 : _currentRow;
		UpdateMaxDisplayCurrentRow();
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

	int Inventory::BeginCurrentRow()
	{
		return _currentRow * _maxDisplayWidth;
	}

	int Inventory::EndCurrentRow()
	{
		return _currentRow * _maxDisplayWidth + _maxDisplayCurrentRow;
	}

	int Inventory::GetMaxDisplayCurrentRow()
	{
		return _maxDisplayCurrentRow;
	}

	void Inventory::UpdateMaxDisplayCurrentRow()
	{
		_maxDisplayCurrentRow = _maxDisplayWidth < _capacity - _currentRow * _maxDisplayWidth ?
			_maxDisplayWidth : _capacity - _currentRow * _maxDisplayWidth;

		_currentIndex = BeginCurrentRow();
	}
}