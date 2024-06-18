#pragma once

#include <SDL_image.h>
#include <string>

namespace AE
{
	class Texture
	{
	public:
		Texture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~Texture();

		SDL_Texture* GetTexture();
		int GetWidth() const;
		int GetHeight() const;

	private:
		SDL_Texture* _texture;
		int _width;
		int _height;
		bool _colorKeyed;
		Uint8 _kred;
		Uint8 _kgreen;
		Uint8 _kblue;

		bool LoadFromFile(SDL_Renderer* renderer, std::string path);
		void Reset();
	};
}