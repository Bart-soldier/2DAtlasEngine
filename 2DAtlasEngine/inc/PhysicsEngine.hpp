#include "Scene.hpp"
#include "Timer.hpp"

namespace AE
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine() {};
		~PhysicsEngine() {};

		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;

		Timer _deltaTime{};

		void MoveCharacters(Scene* scene);

	private:
		void CheckSceneBoundaries(Scene* scene, Character* character);
	};
}