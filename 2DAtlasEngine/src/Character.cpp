#include "../inc/Character.hpp"

namespace AE
{
	Character::Character(SpriteTexture* texture, int x, int y, int speed) : GameObject(texture, x, y),
		_speed { speed }
	{
		_speedX = 0;
		_speedY = 0;
		_desiredX = _posX;
		_desiredY = _posY;

		if(texture != nullptr) texture->SetLineIndex(DIRECTION_DOWN);
	}

	Character::~Character()
	{
	}

	void Character::StartMoving(Direction direction)
	{
		switch (direction)
		{
			case DIRECTION_UP: _speedY -= _speed; break;
			case DIRECTION_DOWN: _speedY += _speed; break;
			case DIRECTION_LEFT: _speedX -= _speed; break;
			case DIRECTION_RIGHT: _speedX += _speed; break;
		}
	}

	void Character::StopMoving(Direction direction)
	{
		switch (direction)
		{
			case DIRECTION_UP: _speedY += _speed; break;
			case DIRECTION_DOWN: _speedY -= _speed; break;
			case DIRECTION_LEFT: _speedX += _speed; break;
			case DIRECTION_RIGHT: _speedX -= _speed; break;
		}

		if(_texture != nullptr && _speedX == 0 && _speedY == 0) dynamic_cast<SpriteTexture*>(_texture)->SetColumnIndex(0);
	}

	bool Character::Move(Uint32 deltaTime)
	{
		if (_speedX == 0 && _speedY == 0)
			return false;

		_desiredX = _posX + static_cast<float>(_speedX) * (static_cast<float>(deltaTime) / 1000.f);
		_desiredY = _posY + static_cast<float>(_speedY) * (static_cast<float>(deltaTime) / 1000.f);

		if (_texture != nullptr)
		{
			Direction newDirection = _speedX != 0 ? (_speedX < 0 ? DIRECTION_LEFT : DIRECTION_RIGHT) : _speedY < 0 ? DIRECTION_UP : DIRECTION_DOWN;
			if (_currentDirection != newDirection)
			{
				_spriteTimer.Start();
				_currentDirection = newDirection;
				dynamic_cast<SpriteTexture*>(_texture)->SetColumnIndex(0);
			}
			dynamic_cast<SpriteTexture*>(_texture)->SetLineIndex(_currentDirection);

			if (_spriteTimer.GetTicks() > 200)
			{
				dynamic_cast<SpriteTexture*>(_texture)->IncrementColumnIndex();
				_spriteTimer.Start();
			}
		}

		return true;
	}

	void Character::ConfirmMove()
	{
		_posX = _desiredX;
		_posY = _desiredY;
	}

	int Character::GetSpeed()
	{
		return _speed;
	}
}