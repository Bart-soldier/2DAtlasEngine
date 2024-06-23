#pragma once

#include "../inc/Texture.hpp"

namespace AE {

	class SpriteTexture : public Texture
	{
	public:
		SpriteTexture(SDL_Renderer* renderer, std::string path, int lineNb, int columnNb, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue);
		~SpriteTexture();

		int GetWidth() override;
		int GetHeight() override;
		void SetLineIndex(int lineIndex);
		void SetColumnIndex(int columnIndex);

	private:
		int _lineNb;
		int _columnNb;
		int _elementWidth;
		int _elementHeight;
		int _lineIndex;
		int _columnIndex;

		void UpdateRenderClip();
	};
}