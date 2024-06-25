#pragma once

#include "../inc/GameObject.hpp"

namespace AE
{
	class Camera
	{

	public:
		Camera(int width, int height);
		~Camera();

		void FocusOn(GameObject* focusPoint);
		void Unfocus();

		void Bind(int width, int height);
		void UnBind();

		void Update();

		int GetPosX();
		int GetPosY();
		int GetWidth();
		int GetHeight();

	private:
		int _posX;
		int _posY;
		const int _width;
		const int _height;
		int _maxWidth;
		int _maxHeight;

		GameObject* _focusPoint;

		void CenterOn(int x, int y, int width, int height);
	};
}