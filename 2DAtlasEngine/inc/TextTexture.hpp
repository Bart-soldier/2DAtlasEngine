#pragma once

#include "../inc/Texture.hpp"

namespace AE {

	class TextTexture : public Texture
	{
	public:
		TextTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color);
		~TextTexture();
	};
}