#pragma once

#include "../inc/Texture.hpp"

namespace AE {

	class SpriteTexture : public Texture
	{
	public:
		SpriteTexture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~SpriteTexture();
	};
}