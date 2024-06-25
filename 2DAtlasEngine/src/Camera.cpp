#include "../inc/Camera.hpp"

namespace AE
{
	Camera::Camera(int width, int height) : _width { width }, _height { height }
	{
		_posX = _width / 2;
		_posY = _height / 2;
		_focusPoint = nullptr;
		_maxWidth = -1;
		_maxHeight = -1;
	}

	Camera::~Camera()
	{
	}

	void Camera::FocusOn(GameObject* focusPoint)
	{
		_focusPoint = focusPoint;
	}

	void Camera::Unfocus()
	{
		_focusPoint = nullptr;
	}

	void Camera::Bind(int width, int height)
	{
		_maxWidth = width;
		_maxHeight = height;
	}

	void Camera::UnBind()
	{
		_maxWidth = -1;
		_maxHeight = -1;
	}

	void Camera::Update()
	{
		if (_focusPoint != nullptr)
			CenterOn(_focusPoint->GetX(), _focusPoint->GetY(), _focusPoint->GetWidth(), _focusPoint->GetHeight());
	}

	void Camera::CenterOn(int x, int y, int width, int height)
	{
		_posX = (x + width / 2) - _width / 2;
		_posY = (y + height / 2) - _height / 2;

		if (_maxWidth != -1 && _maxHeight != -1) {
			_posX = (_posX < 0) ? 0 : _posX;
			_posX = (_maxWidth < _posX + _width) ? _maxWidth - _width : _posX;

			_posY = (_posY < 0) ? 0 : _posY;
			_posY = (_maxHeight < _posY + _height) ? _maxHeight - _height : _posY;
		}
	}

	int Camera::GetPosX()
	{
		return _posX;
	}

	int Camera::GetPosY()
	{
		return _posY;
	}

	int Camera::GetWidth()
	{
		return _width;
	}

	int Camera::GetHeight()
	{
		return _height;
	}
}