#pragma once

#include "../inc/GameObject.hpp"

namespace AE
{
	/// <summary>A <see cref="GameObject"/> representing a ground element.</summary>
	class SceneObject : public GameObject
	{
	public:
		/// <summary>The different object types for scene representation.</summary>
		enum ObjectType
		{
			TYPE_BACKGROUND,
			TYPE_FOREGROUND,
			TYPE_TOTAL
		};

		/// <param name='texture'>The texture representing the element.</param>
		SceneObject(Texture* texture, ObjectType type, int x = 0, int y = 0);
		~SceneObject();

		/// <summary>Gets this object's <see cref="_type"/>.</summary>
		/// <returns>The <see cref="ObjectType"/> used for scene representation.</returns>
		ObjectType GetType();

	private:
		/// <summary>This object's type.</summary>
		ObjectType _type;
	};
}