#pragma once

#include "../inc/GameObject.hpp"
#include "../inc/Character.hpp"

#include <vector>
#include <string>

namespace AE {

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
		std::vector<Character*> GetCharacters();

		void SetBackground(int x, int y, GameObject* gameObject);
		void SetForeground(int x, int y, GameObject* gameObject);
		void AddCharacter(Character* character);
		void RemoveCharacter(Character* character);

	private:
		std::vector<std::pair<GameObject*, GameObject*>>* _sceneElements;
		std::vector<Character*> _characters;
	};
}