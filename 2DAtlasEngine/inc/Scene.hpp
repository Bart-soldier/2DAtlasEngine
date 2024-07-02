#pragma once

#include "../inc/SceneObject.hpp"
#include "../inc/Character.hpp"

#include <vector>
#include <string>

namespace AE
{
	/// <summary>A scene represents a level as a grid, where every element in the grid has a background and a foreground <see cref="GameObject"/>.</summary>
	class Scene
	{
	public:
		/// <summary>Creates a scene as a grid.</summary>
		/// <param name='width'>The width of the grid representing the scene.</param>
		/// <param name='height'>The height of the grid representing the scene.</param>
		/// <param name='name'>The name of the scene.</param>
		/// <param name='texture'>A pointer to the <see cref="Texture"/> to be applied to all of the scene element's background.</param>
		Scene(int width, int height, std::string name, Texture* texture = nullptr);
		~Scene();

		/// <summary>A scene represents a level as a grid.</summary>
		std::string _name;
		/// <summary>A scene represents a level as a grid.</summary>
		const int _width;
		/// <summary>A scene represents a level as a grid.</summary>
		const int _height;

		/// <summary>Gets the background of an element in the scene using grid coordinates.</summary>
		/// <param name='x'>The x coordinate within the grid.</param>
		/// <param name='y'>The y coordinate within the grid.</param>
		/// <returns>A pointer to the background <see cref="SceneObject"/> at that grid position.</returns>
		SceneObject* GetBackgroundInGrid(int x, int y);
		/// <summary>Gets the foreground of an element in the scene using grid coordinates.</summary>
		/// <param name='x'>The x coordinate within the grid.</param>
		/// <param name='y'>The y coordinate within the grid.</param>
		/// <returns>A pointer to the foreground <see cref="SceneObject"/> at that grid position.</returns>
		SceneObject* GetForegroundInGrid(int x, int y);
		/// <summary>Gets the background of an element in the scene using pixel coordinates.</summary>
		/// <param name='x'>The x coordinate in pixel-space.</param>
		/// <param name='y'>The y coordinate in pixel-space.</param>
		/// <returns>A pointer to the background <see cref="SceneObject"/> at that grid's pixel position.</returns>
		SceneObject* GetBackgroundInPixel(int x, int y);
		/// <summary>Gets the foreground of an element in the scene using pixel coordinates.</summary>
		/// <param name='x'>The x coordinate in pixel-space.</param>
		/// <param name='y'>The y coordinate in pixel-space.</param>
		/// <returns>A pointer to the foreground <see cref="SceneObject"/> at that grid's pixel position.</returns>
		SceneObject* GetForegroundInPixel(int x, int y);
		/// <summary>Gets all the characters present in this scene.</summary>
		/// <returns>A vector of pointers to all <see cref="Character"/> present in this scene.</returns>
		std::vector<Character*> GetCharacters();

		/// <summary>Changes the element in the scene using grid coordinates.</summary>
		/// <param name='x'>The x coordinate within the grid.</param>
		/// <param name='y'>The y coordinate within the grid.</param>
		/// <param name='sceneObject'>A pointer to the <see cref="SceneObject"/> to place at that grid's position.</param>
		void SetInGrid(int x, int y, SceneObject* sceneObject);
		/// <summary>Changes the element in the scene using pixel coordinates.</summary>
		/// <param name='x'>The x coordinate in pixel-space.</param>
		/// <param name='y'>The y coordinate in pixel-space.</param>
		/// <param name='sceneObject'>A pointer to the <see cref="SceneObject"/> to place at that grid's pixel position.</param>
		void SetInPixel(int x, int y, SceneObject* sceneObject);
		/// <summary>Adds a character to the scene.</summary>
		/// <param name='character'>A pointer to the character to add.</param>
		void AddCharacter(Character* character);
		/// <summary>Removes a character to the scene.</summary>
		/// <param name='character'>A pointer to the character to remove.</param>
		void RemoveCharacter(Character* character);

	private:
		/// <summary>A vector representing the scene as a grid, where every element in the grid has a background and a foreground <see cref="GameObject"/>.</summary>
		std::vector<std::pair<SceneObject*, SceneObject*>> _sceneElements;
		/// <returns>A vector of pointers to all <see cref="Character"/> present in this scene.</returns>
		std::vector<Character*> _characters;
	};
}