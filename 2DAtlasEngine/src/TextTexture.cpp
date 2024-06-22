#include "../inc/TextTexture.hpp"

namespace AE
{
	TextTexture::TextTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color)
		: Texture(renderer, TTF_RenderText_Solid(font, text.c_str(), color), false, 0xFF, 0xFF, 0xFF)
	{
	}

	TextTexture::~TextTexture()
	{
	}
}