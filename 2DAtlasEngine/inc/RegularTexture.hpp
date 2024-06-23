#pragma once

#include "../inc/Texture.hpp"

namespace AE
{
	/// <summary>A regular texture is the most common type of texture.
	class RegularTexture : public Texture
	{
	public:
		/// <summary>Creates a texture from a file.</summary>
		/// <param name='renderer'>The renderer used to create the texture.</param>
		/// <param name='path'>The path of the file to load the texture from.</param>
		/// <param name='colorKeyed'>The flag to indicate if the texture is color keyed.</param>
		/// <param name='kred'>The color key's red value.</param>
		/// <param name='kgreen'>The color key's green value.</param>
		/// <param name='kblue'>The color key's blue value.</param>
		RegularTexture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~RegularTexture();
	};
}