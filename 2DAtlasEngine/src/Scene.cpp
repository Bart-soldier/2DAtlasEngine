#include "../inc/Scene.hpp"

namespace Game
{
	Scene::Scene(int width, int height, std::string name, GameObject* background) : _width{ width }, _height{ height }, _name{ name }
	{
		_sceneElements = new std::vector<std::pair<GameObject*, GameObject*>>(width * height, std::make_pair(background, nullptr));
	}

	Scene::~Scene()
	{
	}

	GameObject* Scene::GetBackground(int x, int y)
	{
		return _sceneElements->at(y * _width + x).first;
	}

	GameObject* Scene::GetForeground(int x, int y)
	{
		return _sceneElements->at(y * _width + x).second;
	}

	void Scene::SetBackground(int x, int y, GameObject* gameObject)
	{
		_sceneElements->at(y * _width + x).first = gameObject;
	}

	void Scene::SetForeground(int x, int y, GameObject* gameObject)
	{
		_sceneElements->at(y * _width + x).second = gameObject;
	}
}