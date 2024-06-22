#include "../inc/SpriteTexture.hpp"

namespace AE
{
	SpriteTexture::SpriteTexture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
		: Texture(renderer, IMG_Load(path.c_str()), colorKeyed, kred, kgreen, kblue)
	{
	}

	SpriteTexture::~SpriteTexture()
	{
	}
}