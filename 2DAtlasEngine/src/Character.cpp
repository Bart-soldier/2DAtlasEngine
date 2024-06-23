#include "../inc/Character.hpp"

namespace AE
{
	Character::Character(Texture* texture, int x, int y, int speed) : GameObject(texture, x, y),
		_speed { speed }
	{
		_speedX = 0;
		_speedY = 0;
		_desiredX = _posX;
		_desiredY = _posY;
	}

	Character::~Character()
	{
	}

	void Character::StartMoving(Direction direction)
	{
		switch (direction)
		{
			case UP: _speedY -= _speed; break;
			case DOWN: _speedY += _speed; break;
			case LEFT: _speedX -= _speed; break;
			case RIGHT: _speedX += _speed; break;
		}
	}

	void Character::StopMoving(Direction direction)
	{
		switch (direction)
		{
			case UP: _speedY += _speed; break;
			case DOWN: _speedY -= _speed; break;
			case LEFT: _speedX += _speed; break;
			case RIGHT: _speedX -= _speed; break;
		}
	}

	bool Character::Move(Uint32 deltaTime)
	{
		if (_speedX == 0 && _speedY == 0)
			return false;

		_desiredX = _posX + static_cast<float>(_speedX) * (static_cast<float>(deltaTime) / 1000.f);
		_desiredY = _posY + static_cast<float>(_speedY) * (static_cast<float>(deltaTime) / 1000.f);
		return true;
	}

	void Character::ConfirmMove()
	{
		_posX = _desiredX;
		_posY = _desiredY;
	}
}