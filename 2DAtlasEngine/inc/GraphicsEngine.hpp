#pragma once

#include "../inc/RegularTexture.hpp"
#include "../inc/SpriteTexture.hpp"
#include "../inc/TextTexture.hpp"
#include "../inc/Constants.hpp"
#include "../inc/Camera.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace AE
{
	/// <summary>The graphics engine is responsible for the creation and render of various graphical elements.
	/// <para>It also creates and handles the application's window.</para></summary>
	class GraphicsEngine
	{
	public:
		/// <summary>The different viewport positions.</summary>
		enum Viewport
		{
			FULLSCREEN,
			MINIMAP,
			TOTAL
		};

		/// <summary>The different texture resize options.</summary>
		enum Resize
		{
			RESIZE_NONE,
			RESIZE_ONEQUARTER,
			RESIZE_HALF,
			RESIZE_THREEQUARTERS,
			RESIZE_FULL
		};

		/// <param name='width'>The application window's width.</param>
		/// <param name='height'>The application window's height.</param>
		/// <param name='name'>The application window's name.</param>
		GraphicsEngine(int width, int height, std::string name);
		~GraphicsEngine();

		GraphicsEngine(const GraphicsEngine&) = delete;
		GraphicsEngine& operator=(const GraphicsEngine&) = delete;

		/// <summary>Indicates wether the window should close or not.</summary>
		bool _shouldClose;

		/// <summary>Clears the renderer and sets the draw color to white.</summary>
		void ClearRenderer();
		/// <summary>Sets the viewport used to render to.</summary>
		void SetViewport(Viewport viewportValue);
		/// <summary>Updates the screen using the renderer.</summary>
		void UpdateWindow();

		/// <summary>Creates a texture from a file.</summary>
		/// <param name='path'>The path of the file to load the texture from.</param>
		/// <param name='colorKeyed'>The flag to indicate if the texture is color keyed.</param>
		/// <param name='kred'>The color key's red value.</param>
		/// <param name='kgreen'>The color key's green value.</param>
		/// <param name='kblue'>The color key's blue value.</param>
		/// <returns>A pointer to the created <see cref="RegularTexture"/></returns>
		RegularTexture* CreateRegularTexture(std::string path, bool colorKeyed = false, Uint8 kred = 0xFF, Uint8 kgreen = 0xFF, Uint8 kblue = 0xFF);
		/// <summary>Creates a sprite texture from a file.</summary>
		/// <param name='path'>The path of the file to load the sprite from.</param>
		/// <param name='lineNb'>The number of lines within the sprite.</param>
		/// <param name='columnNb'>The number of columns within the sprite.</param>
		/// <param name='colorKeyed'>The flag to indicate if the texture is color keyed.</param>
		/// <param name='kred'>The color key's red value.</param>
		/// <param name='kgreen'>The color key's green value.</param>
		/// <param name='kblue'>The color key's blue value.</param>
		/// <returns>A pointer to the created <see cref="SpriteTexture"/></returns>
		SpriteTexture* CreateSpriteTexture(std::string path, int lineNb, int columnNb, bool colorKeyed = false, Uint8 kred = 0xFF, Uint8 kgreen = 0xFF, Uint8 kblue = 0xFF);
		/// <summary>Creates a text texture from a file.</summary>
		/// <param name='font'>The font used for the text.</param>
		/// <param name='text'>The text used for the texture.</param>
		/// <param name='color'>The color used for the text.</param>
		/// <returns>A pointer to the created <see cref="TextTexture"/></returns>
		TextTexture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
		/// <summary>Add a texture to the renderer.</summary>
		/// <param name='texture'>The texture to add.</param>
		/// <param name='x'>The x position of the texture.</param>
		/// <param name='y'>The y position of the texture.</param>
		/// <param name='Camera'>A pointer to the camera to render to.</param>
		/// <param name='resize'>Should the texture be resized using the <see cref="TILE_RENDER_FACTOR"/>. Defined by enum <see cref="Resize"/>.</param>
		/// <param name='angle'>The angle used to rotate the texture.</param>
		/// <param name='center'>The center of rotation used to rotate the texture.</param>
		/// <param name='flip'>The type of <see cref="SDL_RendererFlip"/> to be applied to the texture.</param>
		void RenderTexture(Texture* texture, int x = 0, int y = 0, Camera* camera = nullptr, Resize resize = RESIZE_FULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		/// <summary>Add a texture to the renderer by enlarging it to fit the full viewport.</summary>
		/// <param name='texture'>The texture to add.</param>
		void RenderTextureFullViewport(Texture* texture);

	private:
		/// <summary>The application's window.</summary>
		SDL_Window* _window;
		/// <summary>The application window's name.</summary>
		std::string _name;
		/// <summary>The application window's width.</summary>
		const int _width;
		/// <summary>The application window's height.</summary>
		const int _height;

		/// <summary>The renderer used to render on the window.</summary>
		SDL_Renderer* _renderer;
		/// <summary>The viewport used to render to.</summary>
		SDL_Rect _viewport;

		/// <summary>Initializes the application's window.</summary>
		bool InitializeWindow();
		/// <summary>Initializes the renderer used to render on the window.</summary>
		bool InitializeRenderer();
		/// <summary>Initializes the various SDL librairies used.</summary>
		bool InitializeLibraries();
	};
}