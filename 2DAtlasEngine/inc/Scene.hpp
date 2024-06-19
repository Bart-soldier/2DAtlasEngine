#pragma once

#include "../inc/GameObject.hpp"

#include <vector>
#include <string>

namespace Game {

	class Scene
	{
	public:
		Scene(int width, int height, std::string name, GameObject* background = nullptr);
		~Scene();

		std::string _name;
		const int _width;
		const int _height;

		GameObject* GetBackground(int x, int y);
		GameObject* GetForeground(int x, int y);

		void SetBackground(int x, int y, GameObject* gameObject);
		void SetForeground(int x, int y, GameObject* gameObject);

	private:
		std::vector<std::pair<GameObject*, GameObject*>>* _sceneElements;
	};
}