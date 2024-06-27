#include "../inc/Scene.hpp"

namespace AE
{
	Scene::Scene(int width, int height, std::string name, GameObject* background) : _width{ width }, _height{ height }, _name{ name }
	{
		_sceneElements = new std::vector<std::pair<GameObject*, GameObject*>>(width * height, std::make_pair(background, nullptr));
	}

	Scene::~Scene()
	{
	}

	GameObject* Scene::GetBackgroundInGrid(int x, int y)
	{
		return (x < 0 || x >= _width || y < 0 || y >= _height) ?
			nullptr : _sceneElements->at(y * _width + x).first;
	}

	GameObject* Scene::GetForegroundInGrid(int x, int y)
	{
		return (x < 0 || x >= _width || y < 0 || y >= _height) ?
			nullptr : _sceneElements->at(y * _width + x).second;
	}

	GameObject* Scene::GetBackgroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		return (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height) ?
			nullptr : _sceneElements->at(gridY * _width + gridX).first;
	}

	GameObject* Scene::GetForegroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		return (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height) ?
			nullptr : _sceneElements->at(gridY * _width + gridX).second;
	}

	std::vector<Character*> Scene::GetCharacters()
	{
		return _characters;
	}

	void Scene::SetBackgroundInGrid(int x, int y, GameObject* gameObject)
	{
		if (!(x < 0 || x >= _width || y < 0 || y >= _height))
			_sceneElements->at(y * _width + x).first = gameObject;
	}

	void Scene::SetForegroundInGrid(int x, int y, GameObject* gameObject)
	{
		if (!(x < 0 || x >= _width || y < 0 || y >= _height))
			_sceneElements->at(y * _width + x).second = gameObject;
	}

	void Scene::SetBackgroundInPixel(int x, int y, GameObject* gameObject)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (!(gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height))
			_sceneElements->at(gridY * _width + gridX).first = gameObject;
	}

	void Scene::SetForegroundInPixel(int x, int y, GameObject* gameObject)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (!(gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height))
			_sceneElements->at(gridY * _width + gridX).second = gameObject;
	}

	void Scene::AddCharacter(Character* character)
	{
		_characters.push_back(character);
	}

	void Scene::RemoveCharacter(Character* character)
	{
		_characters.erase(std::remove(_characters.begin(), _characters.end(), character), _characters.end());
	}

}