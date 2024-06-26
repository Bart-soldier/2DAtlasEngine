#pragma once

#include "../inc/Texture.hpp"
#include "../inc/SpriteTexture.hpp"

#include <typeinfo>

namespace AE
{
	/// <summary>A polymorphic class defining any and all types of objects within the game.</summary>
	class GameObject
	{
	public:
		/// <param name='texture'>The texture representing the game object.</param>
		/// <param name='x'>The character's initial x position.</param>
		/// <param name='y'>The character's initial y position.</param>
		GameObject(Texture* texture = NULL, int x = 0, int y = 0);
		~GameObject();

		void SetBoundingBox(int x, int y, int width, int height);
		void SetX(int x);
		void SetY(int y);

		Texture* GetTexture();
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		SDL_Rect GetBoundingBox();

	protected:
		/// <summary>The game object's x coordinate.</summary>
		float _posX;
		/// <summary>The game object's x coordinate.</summary>
		float _posY;
		/// <summary>The game object's width.</summary>
		int _width;
		/// <summary>The game object's height.</summary>
		int _height;

		/// <summary>The game object's bounding box for collisions.
		/// <para>Corresponds to its texture's width and height by default.</para></summary>
		SDL_Rect _boundingBox;

	private:
		/// <summary>The game object's texture.</summary>
		Texture* _texture;
	};
}