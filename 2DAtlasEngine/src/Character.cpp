#include "../inc/Character.hpp"

namespace Game
{
	Character::Character(AE::Texture* texture, int x, int y) : GameObject(texture, x, y)
	{
	}

	Character::~Character()
	{
	}
}