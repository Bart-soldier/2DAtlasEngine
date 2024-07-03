#include "../inc/Scene.hpp"

namespace AE
{
	Scene::Scene(int width, int height, std::string name, Texture* texture) : _width{ width }, _height{ height }, _name{ name }
	{
		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				_sceneElements.push_back(std::make_pair(new SceneObject(texture, SceneObject::TYPE_BACKGROUND, x * TILE_RENDER_SIZE, y * TILE_RENDER_SIZE), nullptr));
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

	SceneObject* Scene::GetBackgroundInGrid(int x, int y)
	{
		return (x < 0 || x >= _width || y < 0 || y >= _height) ?
			nullptr : _sceneElements.at(y * _width + x).first;
	}

	SceneObject* Scene::GetForegroundInGrid(int x, int y)
	{
		return (x < 0 || x >= _width || y < 0 || y >= _height) ?
			nullptr : _sceneElements.at(y * _width + x).second;
	}

	SceneObject* Scene::GetBackgroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		return (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height) ?
			nullptr : _sceneElements.at(gridY * _width + gridX).first;
	}

	SceneObject* Scene::GetForegroundInPixel(int x, int y)
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

	void Scene::SetInGrid(int x, int y, SceneObject* sceneObject)
	{
		if (sceneObject == nullptr) return;

		if (!(x < 0 || x >= _width || y < 0 || y >= _height))
		{
			sceneObject->SetXInPixel(x * TILE_RENDER_SIZE);
			sceneObject->SetYInPixel(y * TILE_RENDER_SIZE);

			switch (sceneObject->GetType())
			{
				case SceneObject::TYPE_BACKGROUND:
					delete _sceneElements.at(y * _width + x).first;
					_sceneElements.at(y * _width + x).first = sceneObject;
					break;
				case SceneObject::TYPE_FOREGROUND:
					delete _sceneElements.at(y * _width + x).second;
					_sceneElements.at(y * _width + x).second = sceneObject;
					break;
			}
		}
	}

	void Scene::SetInPixel(int x, int y, SceneObject* sceneObject)
	{
		if (sceneObject == nullptr) return;

		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (!(gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height))
		{
			sceneObject->SetXInPixel(x);
			sceneObject->SetYInPixel(y);
			switch (sceneObject->GetType())
			{
				case SceneObject::TYPE_BACKGROUND:
					delete _sceneElements.at(y * _width + x).first;
					_sceneElements.at(gridY * _width + gridX).first = sceneObject;
					break;
				case SceneObject::TYPE_FOREGROUND:
					delete _sceneElements.at(y * _width + x).second;
					_sceneElements.at(gridY * _width + gridX).second = sceneObject;
					break;
			}
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

	void Scene::RemoveBackgroundInGrid(int x, int y)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			_sceneElements.at(y * _width + x).first = nullptr;
	}

	void Scene::RemoveForegroundInGrid(int x, int y)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			_sceneElements.at(y * _width + x).second = nullptr;
	}

	void Scene::RemoveBackgroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height)
			_sceneElements.at(gridY * _width + gridX).first = nullptr;
	}

	void Scene::RemoveForegroundInPixel(int x, int y)
	{
		int gridX = x / TILE_RENDER_SIZE;
		int gridY = y / TILE_RENDER_SIZE;
		if (gridX < 0 || gridX >= _width || gridY < 0 || gridY >= _height)
			_sceneElements.at(gridY * _width + gridX).second = nullptr;
	}
}