#pragma once

#include "../inc/GameObject.hpp"

namespace AE
{
	/// <summary>A <see cref="GameObject"/> with movement capabilities.</summary>
	class Character : public GameObject
	{
	public:
		/// <param name='texture'>The texture representing the character.</param>
		/// <param name='x'>The character's initial x position.</param>
		/// <param name='y'>The character's initial y position.</param>
		/// <param name='speed'>The character's speed, in pixel per seconds.</param>
		Character(Texture* texture, int x, int y, int speed);
		~Character();

		/// <summary>The x coordinate the character desires to move to.</summary>
		float _desiredX;
		/// <summary>The y coordinate the character desires to move to.</summary>
		float _desiredY;

		/// <summary>Increases the speed on a specific axis to enable movement.</summary>
		/// <param name='direction'>The direction of the movement.</param>
		void StartMoving(Direction direction);
		/// <summary>Decreases the speed on a specific axis to disable movement.</summary>
		/// <param name='direction'>The direction of the movement.</param>
		void StopMoving(Direction direction);
		/// <summary>Updates the <see cref="_desiredX"/> and <see cref="_desiredY"/> depending on the axis speed.
		/// <para>Use <see cref="StartMoving(Direction direction)"/> and <see cref="StopMoving(Direction direction)"/>
		/// to enable and disable movement.</para>
		/// </summary>
		/// <param name='deltaTime'>The time spent since last frame.</param>
		bool Move(Uint32 deltaTime);
		/// <summary>Applies the <see cref="_desiredX"/> and <see cref="_desiredY"/> to the character's x and y coordinates.</summary>
		/// <returns>True if any movement occured,
		/// <para>False otherwise.</para></returns>
		void ConfirmMove();

	private:
		/// <summary>The character's speed, in pixel per seconds.</summary>
		int _speed;
		/// <summary>The current speed on the x axis.</summary>
		int _speedX;
		/// <summary>The current speed on the y axis.</summary>
		int _speedY;
	};
}