#pragma once

#include "Constants.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

namespace AE
{
	class Texture
	{
	public:
		Texture(SDL_Renderer* renderer, SDL_Surface* surfacebool, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~Texture();

		void SetColor(Uint8 red, Uint8 green, Uint8 blue);
		void SetBlendMode(SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);
		void SetAlpha(Uint8 alpha);

		SDL_Texture* GetTexture();
		virtual int GetWidth();
		virtual int GetHeight();
		SDL_Rect* GetRenderClip();

	protected:
		SDL_Texture* _texture;
		int _width;
		int _height;
		SDL_Rect _renderClip;
		void Reset();

	private:
		bool _colorKeyed;
		Uint8 _kred;
		Uint8 _kgreen;
		Uint8 _kblue;

		bool LoadFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
	};
}