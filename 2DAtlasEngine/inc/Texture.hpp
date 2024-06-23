#pragma once

#include "Constants.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

namespace AE
{
	/// <summary>A polymorphic class defining any and all types of textures within the game.</summary>
	class Texture
	{
	public:
		/// <summary>Creates a texture from a surface.</summary>
		/// <param name='renderer'>The renderer used to create the texture.</param>
		/// <param name='surface'>The surface to create the texture from.</param>
		/// <param name='colorKeyed'>The flag to indicate if the texture is color keyed.</param>
		/// <param name='kred'>The color key's red value.</param>
		/// <param name='kgreen'>The color key's green value.</param>
		/// <param name='kblue'>The color key's blue value.</param>
		Texture(SDL_Renderer* renderer, SDL_Surface* surface, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~Texture();

		/// <summary>Changes a textures color values.</summary>
		/// <param name='red'>The texture's new red value.</param>
		/// <param name='green'>The texture's new green value.</param>
		/// <param name='blue'>The texture's new blue value.</param>
		void SetColor(Uint8 red, Uint8 green, Uint8 blue);
		/// <summary>Changes a texture's alpha blend mode.</summary>
		/// <param name='blendMode'>The texture's new alpha blend mode.</param>
		void SetBlendMode(SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);
		/// <summary>Changes a texture's alpha value</summary>
		/// <param name='blendMode'>The texture's new alpha value.</param>
		void SetAlpha(Uint8 alpha);

		SDL_Texture* GetTexture();
		virtual int GetWidth();
		virtual int GetHeight();
		SDL_Rect* GetRenderClip();

	protected:
		/// <summary>The texture itself.</summary>
		SDL_Texture* _texture;
		/// <summary>The texture's width.</summary>
		int _width;
		/// <summary>The texture's height</summary>
		int _height;
		/// <summary>The part of the texture to render.</summary>
		SDL_Rect _renderClip;
		/// <summary>Destroys the texture and resets all of its values.</summary>
		void Reset();

	private:
		/// <summary>The flag to indicate if the texture is color keyed.</summary>
		bool _colorKeyed;
		/// <summary>The color key's red value.</summary>
		Uint8 _kred;
		/// <summary>The color key's green value.</summary>
		Uint8 _kgreen;
		/// <summary>The color key's blue value.</summary>
		Uint8 _kblue;

		/// <summary>Creates a texture from a surface.</summary>
		/// <param name='renderer'>The renderer used to create the texture.</param>
		/// <param name='surface'>The surface to create the texture from.</param>
		bool LoadFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
	};
}