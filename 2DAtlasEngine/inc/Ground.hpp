#pragma once

#include "../inc/GameObject.hpp"

namespace AE
{
	/// <summary>A <see cref="GameObject"/> representing a ground element.</summary>
	class Ground : public GameObject
	{
	public:
		/// <param name='texture'>The texture representing the element.</param>
		Ground(Texture* texture);
		~Ground();
	};
}