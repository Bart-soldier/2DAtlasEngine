#pragma once

#include "../inc/Texture.hpp"

namespace AE
{
	/// <summary>A sprite texture is used to display sprites.
	class SpriteTexture : public Texture
	{
	public:
		/// <summary>Creates a sprite texture from a file.</summary>
		/// <param name='renderer'>The renderer used to create the texture.</param>
		/// <param name='path'>The path of the file to load the sprite from.</param>
		/// <param name='lineNb'>The number of lines within the sprite.</param>
		/// <param name='columnNb'>The number of columns within the sprite.</param>
		/// <param name='colorKeyed'>The flag to indicate if the texture is color keyed.</param>
		/// <param name='kred'>The color key's red value.</param>
		/// <param name='kgreen'>The color key's green value.</param>
		/// <param name='kblue'>The color key's blue value.</param>
		SpriteTexture(SDL_Renderer* renderer, std::string path, int lineNb, int columnNb, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~SpriteTexture();

		/// <summary>Gets the width of a single element within the sprite.</summary>
		int GetWidth() override;
		/// <summary>Gets the height of a single element within the sprite.</summary>
		int GetHeight() override;
		/// <summary>Specifies which line of the sprite to look at when rendering.</summary>
		void SetLineIndex(int lineIndex);
		/// <summary>Specifies which column of the sprite to look at when rendering.</summary>
		void SetColumnIndex(int columnIndex);
		/// <summary>Increments the column of the sprite to look at when rendering.</summary>
		void IncrementColumnIndex();

	private:
		/// <summary>The number of lines within the sprite.</summary>
		int _lineNb;
		/// <summary>The number of column within the sprite.</summary>
		int _columnNb;
		/// <summary>The width of a single element within the sprite.</summary>
		int _elementWidth;
		/// <summary>The height of a single element within the sprite.</summary>
		int _elementHeight;
		/// <summary>The line of the sprite to look at when rendering.</summary>
		int _lineIndex;
		/// <summary>The column of the sprite to look at when rendering.</summary>
		int _columnIndex;

		/// <summary>Updates the render clip depending on the sprite's <see cref="_lineIndex"/> and <see cref="_columnIndex"/>.</summary>
		void UpdateRenderClip();
	};
}