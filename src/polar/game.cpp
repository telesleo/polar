#include "game.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>

#include <cstdint>
#include <string>

#include "input.h"

namespace polar
{
	Game::Game(char* windowTitle, uint16_t windowWidth, uint16_t windowHeight)
		: _windowTitle(windowTitle), _windowWidth(windowWidth), _windowHeight(windowHeight)
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

		_window = SDL_CreateWindow
		(
			_windowTitle, _windowWidth, _windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
		);

		_context = SDL_GL_CreateContext(_window);
		SDL_GL_MakeCurrent(_window, _context);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			SDL_Log("Failed to initialize OpenGL context");
		}

		Input input;
		Renderer renderer;

		bool running = true;

		input.onKeyPressed
		(
			SDL_EVENT_QUIT,
			[&running]()
			{
				running = false;
			}
		);

		while (running)
		{
			input.update();
			renderer.update(_window);
		}
	}

	Game::~Game()
	{
		SDL_GL_DestroyContext(_context);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}
}
