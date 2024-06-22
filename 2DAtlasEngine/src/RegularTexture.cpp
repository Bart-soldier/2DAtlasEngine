#include "../inc/RegularTexture.hpp"

namespace AE
{
	RegularTexture::RegularTexture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
		: Texture(renderer, IMG_Load(path.c_str()), colorKeyed, kred, kgreen, kblue)
	{
	}

	RegularTexture::~RegularTexture()
	{
	}
}