#include "game.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>

#include <iostream>
#include <cstdint>
#include <string>

#include "input.h"

namespace polar
{
	Game::Game(char* windowTitle, uint16_t windowWidth, uint16_t windowHeight)
		: _windowTitle(windowTitle), _windowWidth(windowWidth), _windowHeight(windowHeight)
	{

	}

	void Game::start()
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

		SDL_Window* window = SDL_CreateWindow(
			_windowTitle, _windowWidth, _windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
		);

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
		}

		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}
