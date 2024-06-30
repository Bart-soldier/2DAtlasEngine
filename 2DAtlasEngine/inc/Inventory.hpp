#pragma once

#include "../inc/GameObject.hpp"

#include <vector>

namespace AE
{
	/// <summary>The <see cref="Inventory"/> is used to store <see cref="GameObjects"/>, as well as provide various elements for displaying the inventory bar.</summary>
	class Inventory
	{
	public:
		/// <summary>The <see cref="Inventory"/> is used to store <see cref="GameObjects"/>, as well as provide various elements for displaying the inventory bar.</summary>
		/// <param name='texture'>The texture used for displaying the inventory bar. Best used if first column of sprite is regular display and second column is the display when selected.</param>
		/// <param name='capacity'>The amount of <see cref="GameObjects"/> the inventory can hold.</param>
		Inventory(SpriteTexture* texture, int capacity);
		~Inventory();

		/// <summary>Increments the index used to know which element of the inventory is selected in the inventory bar.<summary>
		void IncrementIndex();
		/// <summary>Decrements the index used to know which element of the inventory is selected in the inventory bar.<summary>
		void DecrementIndex();
		/// <summary>Adds an item to the inventory at a specific index, if it is within the capacity.<summary>
		/// <param name='item'>The <see cref="GameObject"/> to add to the inventory.</param>
		/// <param name='index'>The index at which to add it.</param>
		/// <returns>True if the item could be added,
		/// <para>False otherwise.</para></returns>
		bool AddAt(GameObject* item, int index);
		/// <summary>Adds an item to the inventory, if it has not reached max capacity.<summary>
		/// <param name='item'>The <see cref="GameObject"/> to add to the inventory.</param>
		/// <returns>True if the item could be added,
		/// <para>False otherwise.</para></returns>
		bool Add(GameObject* item);
		/// <summary>Increments the row of displayed elements within the inventory bar.<summary>
		void IncrementRow();
		/// <summary>Decrements the row of displayed elements within the inventory bar.<summary>
		void DecrementRow();

		/// <summary> Gets the inventory's <see cref="_texture"/>.</summary>
		/// <returns>The texture used for displaying the inventory bar.</returns>
		SpriteTexture* GetTexture();
		/// <summary> Gets the inventory's <see cref="_capacity"/>.</summary>
		/// <returns>The amount of <see cref="GameObjects"/> the inventory can hold.</returns>
		int GetCapacity();
		/// <summary> Gets the inventory's <see cref="_currentIndex"/>.</summary>
		/// <returns>The index used to know which element of the inventory is selected in the inventory bar.</returns>
		int GetCurrentIndex();
		/// <summary> Gets a specific element from the inventory.</summary>
		/// <param name='index'>The index of the element to retrieve.</param>
		/// <returns>The <see cref="GameObjects"/> at that inventory position,
		/// <para>nullptr if not found or out of bounds.</para></returns>
		GameObject* GetAt(int index);
		/// <summary> Gets the item at the <see cref="_currentIndex"/> position within the inventory.</summary>
		/// <returns>The <see cref="GameObjects"/> at said position,
		/// <para>nullptr if not found or out of bounds.</para></returns>
		GameObject* GetAtCurrentIndex();
		/// <summary> Gets the inventory's <see cref="_currentRow"/>'s begin element.</summary>
		/// <returns>The first element of the row to display on the inventory bar.</returns>
		int BeginCurrentRow();
		/// <summary> Gets the inventory's <see cref="_currentRow"/>'s end element.</summary>
		/// <returns>The last element of the row to display on the inventory bar.</returns>
		int EndCurrentRow();
		/// <summary> Gets the inventory's <see cref="_maxDisplayCurrentRow"/>.</summary>
		/// <returns>The maximum amount of elements to display for this row of the inventory bar.</returns>
		int GetMaxDisplayCurrentRow();

	private:
		/// <summary>The texture used for displaying the inventory bar. Best used if first column of sprite is regular display and second column is the display when selected.<summary>
		SpriteTexture* _texture;
		std::vector<GameObject*> _items;
		/// <summary>The amount of <see cref="GameObjects"/> the inventory can hold.</summary>
		int _capacity;
		/// <summary>The space currently used by the inventory.</summary>
		int _spaceUsed;
		/// <summary>The index used to know which element of the inventory is selected in the inventory bar.<summary>
		int _currentIndex;

		/// <summary>The maximum amout of items that can be displayed on one row of an inventory bar.<summary>
		int _maxDisplayWidth;
		/// <summary>The total number of row constituting the inventory bar.<summary>
		int _rowNb;
		/// <summary>The current row to display for the inventory bar.<summary>
		int _currentRow;
		/// <summary>The maximum amount of elements to display for this row of the inventory bar.<summary>
		int _maxDisplayCurrentRow;

		/// <summary>Updates the maximum amount of elements to display for this row of the inventory bar.<summary>
		void UpdateMaxDisplayCurrentRow();
	};
}