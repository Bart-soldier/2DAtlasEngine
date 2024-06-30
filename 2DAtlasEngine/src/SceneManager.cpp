#include "../inc/SceneManager.hpp"

namespace AE
{
	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
		for (Scene* scene : _scenes)
			delete scene;
	}

	void SceneManager::AddScene(Scene* scene)
	{
		_scenes.push_back(scene);
	}

	void SceneManager::RemoveScene(Scene* scene)
	{
		_scenes.erase(std::remove(_scenes.begin(), _scenes.end(), scene), _scenes.end());
	}


	void SceneManager::SetCurrentSceneIndex(int index)
	{
		_currentSceneIndex = (index >= 0 && index < _scenes.size()) ? index : _currentSceneIndex;
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return _scenes.at(_currentSceneIndex);
	}
}