#include "../inc/SpriteTexture.hpp"

namespace AE
{
	SpriteTexture::SpriteTexture(SDL_Renderer* renderer, std::string path, int lineNb, int columnNb, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
		: Texture(renderer, IMG_Load(path.c_str()), colorKeyed, kred, kgreen, kblue),
		_lineNb{ lineNb }, _columnNb{ columnNb }
	{
		_elementWidth = _width / _lineNb;
		_elementHeight = _height / _columnNb;
		_lineIndex = 0;
		_columnIndex = 0;
		UpdateRenderClip();
	}

	SpriteTexture::~SpriteTexture()
	{
		Reset();
	}

	int SpriteTexture::GetWidth()
	{
		return _elementWidth;
	}

	int SpriteTexture::GetHeight()
	{
		return _elementHeight;
	}

	void SpriteTexture::SetLineIndex(int lineIndex)
	{
		_lineIndex = lineIndex;
		UpdateRenderClip();
	}

	void SpriteTexture::SetColumnIndex(int columnIndex)
	{
		_columnIndex = columnIndex;
		UpdateRenderClip();
	}

	void SpriteTexture::UpdateRenderClip()
	{
		_renderClip = { _lineIndex * _elementWidth, _columnIndex * _elementHeight, _elementWidth, _elementHeight };
	}
}