#pragma once

#include "../inc/GameObject.hpp"

namespace AE {

	class Character : public GameObject
	{
	public:
		Character(Texture* texture, int x, int y, int speed);
		~Character();

		float _desiredX;
		float _desiredY;

		void StartMoving(Direction direction);
		void StopMoving(Direction direction);
		bool Move(Uint32 deltaTime);
		void ConfirmMove();

	private:
		int _speed;
		int _speedX;
		int _speedY;
	};
}