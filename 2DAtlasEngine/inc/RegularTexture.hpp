#pragma once

#include "../inc/Texture.hpp"

namespace AE {

	class RegularTexture : public Texture
	{
	public:
		RegularTexture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~RegularTexture();
	};
}