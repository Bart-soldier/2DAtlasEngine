#include "../inc/Texture.hpp"

namespace AE
{
	Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surface, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
	{
		Reset();

		_colorKeyed = colorKeyed;
		_kred = kred;
		_kgreen = kgreen;
		_kblue = kblue;

		LoadFromSurface(renderer, surface);
	}

	Texture::~Texture()
	{
		Reset();
	}

	void Texture::Reset()
	{
		if (_texture != nullptr)
			SDL_DestroyTexture(_texture);

		_texture = nullptr;
		_width = 0;
		_height = 0;
		_renderClip = { 0, 0, 0, 0 };

		_colorKeyed = false;
		_kred = 0xFF;
		_kblue = 0xFF;
		_kgreen = 0xFF;
	}

	bool Texture::LoadFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
	{
		if (surface == NULL)
		{
			printf("Unable to load image! SDL Error: %s\n", IMG_GetError());
			return false;
		}

		if(_colorKeyed)
			SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, _kred, _kgreen, _kblue));

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		_texture = texture;
		_width = surface->w < TILE_SIZE ? TILE_SIZE : surface->w;
		_height = surface->h < TILE_SIZE ? TILE_SIZE : surface->h;
		_renderClip = { 0, 0, _width, _height };

		SDL_FreeSurface(surface);

		return true;
	}

	void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		SDL_SetTextureColorMod(_texture, red, green, blue);
	}

	void Texture::SetBlendMode(SDL_BlendMode blendMode)
	{
		SDL_SetTextureBlendMode(_texture, blendMode);
	}

	void Texture::SetAlpha(Uint8 alpha)
	{
		SDL_SetTextureAlphaMod(_texture, alpha);
	}

	SDL_Texture* Texture::GetTexture()
	{
		return _texture;
	}

	int Texture::GetWidth()
	{
		return _width;
	}

	int Texture::GetHeight()
	{
		return _height;
	}

	SDL_Rect* Texture::GetRenderClip()
	{
		return &_renderClip;
	}
}