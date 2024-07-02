#include "../inc/SceneObject.hpp"

namespace AE
{
	SceneObject::SceneObject(Texture* texture, ObjectType type, int x, int y) : GameObject(texture, x, y), _type { type }
	{
	}

	SceneObject::~SceneObject()
	{
	}

	SceneObject::ObjectType SceneObject::GetType()
	{
		return _type;
	}
}