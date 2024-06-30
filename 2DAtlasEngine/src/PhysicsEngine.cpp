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

	void PhysicsEngine::MoveCharacter(Character* character, Scene* scene)
	{
		if (!character->Move(_deltaTime.GetTicks()))
			return;

		CheckSceneBoundaries(scene, character);

		character->ConfirmMove();
	}

	void PhysicsEngine::StartDeltaTime()
	{
		_deltaTime.Start();
	}

	void PhysicsEngine::CheckSceneBoundaries(Scene* scene, Character* character)
	{
		SDL_Rect collisionBox = character->GetBoundingBox();

		if (character->_desiredX + collisionBox.x < 0)
			character->_desiredX = 0 - collisionBox.x;
		else if (character->_desiredX + collisionBox.x + collisionBox.w >= scene->_width * TILE_RENDER_SIZE)
			character->_desiredX = scene->_width * TILE_RENDER_SIZE - (collisionBox.x + collisionBox.w);

		if (character->_desiredY + collisionBox.y < 0)
			character->_desiredY = 0 - collisionBox.y;
		else if (character->_desiredY + collisionBox.y + collisionBox.h >= scene->_height * TILE_RENDER_SIZE)
			character->_desiredY = scene->_height * TILE_RENDER_SIZE - (collisionBox.y + collisionBox.h);
	}
}