#include "../inc/PhysicsEngine.hpp"

namespace AE
{
	void PhysicsEngine::MoveCharacters(Scene* scene)
	{
		for (Character* character : scene->GetCharacters())
		{
			if(!character->Move(_deltaTime.GetTicks()))
				continue;

			CheckSceneBoundaries(scene, character);

			character->ConfirmMove();
		}
	}

	void PhysicsEngine::CheckSceneBoundaries(Scene* scene, Character* character)
	{
		if (character->_desiredX + character->_boundingBox.x < 0)
			character->_desiredX = 0 - character->_boundingBox.x;
		else if (character->_desiredX + character->_boundingBox.x + character->_boundingBox.w >= scene->_width * TILE_RENDER_SIZE)
			character->_desiredX = scene->_width * TILE_RENDER_SIZE - (character->_boundingBox.x + character->_boundingBox.w);

		if (character->_desiredY + character->_boundingBox.y < 0)
			character->_desiredY = 0 - character->_boundingBox.y;
		else if (character->_desiredY + character->_boundingBox.y + character->_boundingBox.h >= scene->_height * TILE_RENDER_SIZE)
			character->_desiredY = scene->_height * TILE_RENDER_SIZE - (character->_boundingBox.y + character->_boundingBox.h);
	}
}