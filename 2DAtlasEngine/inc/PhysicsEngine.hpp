#include "Scene.hpp"
#include "Timer.hpp"

namespace AE
{
	/// <summary>The physics engine is responsible to move objects and check for collisions.</summary>
	class PhysicsEngine
	{
	public:
		PhysicsEngine() {};
		~PhysicsEngine() {};

		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;

		/// <summary>Timer used to know the time spent between two frames.</summary>
		Timer _deltaTime{};

		/// <summary>Moves all the characters in a scene, while checking for collisions.</summary>
		/// <param name='scene'>The scene containing the characters.</param>
		void MoveCharacters(Scene* scene);

	private:
		/// <summary>Checks if a character is within the boundaries of a scene.</summary>
		/// <param name='scene'>The scene containing the character.</param>
		/// <param name='character'>The character to check.</param>
		void CheckSceneBoundaries(Scene* scene, Character* character);
	};
}