#pragma once

#include "../inc/Scene.hpp"

#include <vector>

namespace AE
{
	/// <summary>Manages everything <see cref="Scene"/>-related within the game.</summary>
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);

		void SetCurrentSceneIndex(int index);

		Scene* GetCurrentScene();

	private:
		std::vector<Scene*> _scenes{};
		int _currentSceneIndex = -1;
	};
}