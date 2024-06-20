#include "../inc/Texture.hpp"

namespace AE
{
	Texture::Texture(SDL_Renderer* renderer, std::string path, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
	{
		Reset();

		_colorKeyed = colorKeyed;
		_kred = kred;
		_kgreen = kgreen;
		_kblue = kblue;

		LoadFromSurface(renderer, IMG_Load(path.c_str()));
	}

	Texture::Texture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color)
	{
		Reset();
		LoadFromSurface(renderer, TTF_RenderText_Solid(font, text.c_str(), color));
	}

	Texture::~Texture()
	{
		Reset();
	}

	void Texture::Reset()
	{
		if (_texture != NULL)
			SDL_DestroyTexture(_texture);

		_texture = NULL;
		_width = 0;
		_height = 0;
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
		_width = surface->w;
		_height = surface->h;

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

	int Texture::GetWidth() const
	{
		return _width;
	}

	int Texture::GetHeight() const
	{
		return _height;
	}
}