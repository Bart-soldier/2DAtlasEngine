#pragma once

#include "../inc/Texture.hpp"

namespace AE
{
	/// <summary>A text texture is used to display text.
	class TextTexture : public Texture
	{
	public:
		/// <summary>Creates a text texture from a file.</summary>
		/// <param name='renderer'>The renderer used to create the texture.</param>
		/// <param name='font'>The font used for the text.</param>
		/// <param name='text'>The text used for the texture.</param>
		/// <param name='color'>The color used for the text.</param>
		TextTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color);
		~TextTexture();
	};
}