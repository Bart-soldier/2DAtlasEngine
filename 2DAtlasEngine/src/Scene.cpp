#include "../inc/Scene.hpp"

namespace AE
{
	Scene::Scene(int width, int height, std::string name, Texture* texture) : _width{ width }, _height{ height }, _name{ name }
	{
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				_sceneElements.push_back(std::make_pair(new GameObject(texture, x * TILE_RENDER_SIZE, y * TILE_RENDER_SIZE), nullptr));
	}

	Scene::~Scene()
	{
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				delete GetBackgroundInGrid(x, y);
				delete GetForegroundInGrid(x, y);
			}
		}
	}

	GameObject* Scene::GetBackgroundInGrid(int x, int y)
	{
		return (x < 0 || x >= _width || y < 0 || y >= _height) ?
			nullptr : _sceneElements.at(y * _width + x).first;
	}

	GameObject* Scene::GetForegroundInGrid(int x, int y)
	{
		return (x < 0 || x >= _width || y < 0 || y >= _height) ?
			nullptr : _sceneElements.at(y * _width + x).second;
	}

	GameObject* Scene::GetBackgroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		return (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height) ?
			nullptr : _sceneElements.at(gridY * _width + gridX).first;
	}

	GameObject* Scene::GetForegroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		return (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height) ?
			nullptr : _sceneElements.at(gridY * _width + gridX).second;
	}

	std::vector<Character*> Scene::GetCharacters()
	{
		return _characters;
	}

	void Scene::SetBackgroundInGrid(int x, int y, GameObject* gameObject)
	{
		if (!(x < 0 || x >= _width || y < 0 || y >= _height))
		{
			gameObject->SetXInPixel(x * TILE_RENDER_SIZE);
			gameObject->SetYInPixel(y * TILE_RENDER_SIZE);
			delete _sceneElements.at(y * _width + x).first;
			_sceneElements.at(y * _width + x).first = gameObject;
		}
	}

	void Scene::SetForegroundInGrid(int x, int y, GameObject* gameObject)
	{
		if (!(x < 0 || x >= _width || y < 0 || y >= _height))
		{
			gameObject->SetXInPixel(x * TILE_RENDER_SIZE);
			gameObject->SetYInPixel(y * TILE_RENDER_SIZE);
			delete _sceneElements.at(y * _width + x).second;
			_sceneElements.at(y * _width + x).second = gameObject;
		}
	}

	void Scene::SetBackgroundInPixel(int x, int y, GameObject* gameObject)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (!(gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height))
		{
			gameObject->SetXInPixel(x);
			gameObject->SetYInPixel(y);
			delete _sceneElements.at(y * _width + x).first;
			_sceneElements.at(gridY * _width + gridX).first = gameObject;
		}
	}

	void Scene::SetForegroundInPixel(int x, int y, GameObject* gameObject)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (!(gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height))
		{
			gameObject->SetXInPixel(x);
			gameObject->SetYInPixel(y);
			delete _sceneElements.at(y * _width + x).second;
			_sceneElements.at(gridY * _width + gridX).second = gameObject;
		}
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