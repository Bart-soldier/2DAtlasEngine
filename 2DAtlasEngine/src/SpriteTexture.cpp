#include "../inc/SpriteTexture.hpp"

namespace AE
{
	SpriteTexture::SpriteTexture(SDL_Renderer* renderer, std::string path, int lineNb, int columnNb, bool colorKeyed, Uint8 kred, Uint8 kgreen, Uint8 kblue)
		: Texture(renderer, IMG_Load(path.c_str()), colorKeyed, kred, kgreen, kblue),
		_lineNb{ lineNb }, _columnNb{ columnNb }
	{
		_elementWidth = _width / _columnNb;
		_elementHeight = _height / _lineNb;
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
		_lineIndex = lineIndex >= _lineNb ? _lineNb - 1 : lineIndex < 0 ? 0 : lineIndex;
		UpdateRenderClip();
	}

	void SpriteTexture::SetColumnIndex(int columnIndex)
	{
		_columnIndex = columnIndex >= _columnNb ? _columnNb - 1 : columnIndex < 0 ? 0 : columnIndex;
		UpdateRenderClip();
	}

	void SpriteTexture::UpdateRenderClip()
	{
		_renderClip = { _columnIndex * _elementWidth, _lineIndex * _elementHeight, _elementWidth, _elementHeight };
	}
}