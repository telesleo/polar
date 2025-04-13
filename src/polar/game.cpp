#include "game.h"

#include <iostream>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <cstdint>
#include <string>

#include "input.h"

namespace polar
{
	Game::Game(char* windowTitle, uint16_t windowWidth, uint16_t windowHeight) :
		displayFPS(false),
		_windowTitle(windowTitle),
		_windowWidth(windowWidth),
		_windowHeight(windowHeight),
		_running(false),
		_frameCount(0),
		_fpsTimer(0),
		_fpsDisplayRate(0.1f)
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

		SDL_GL_SetSwapInterval(0);

		input = std::make_unique<Input>();
		scene = std::make_unique<Scene>();
		renderer = std::make_unique<Renderer>(_window);
	}

	Game::~Game()
	{
		SDL_GL_DestroyContext(_context);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void Game::start()
	{
		_running = true;

		uint64_t last = SDL_GetPerformanceCounter();

		scene->start(*input, *renderer);

		while (_running)
		{
			if (input->quit())
			{
				_running = false;
			}

			if (input->windowResized())
			{
				int width, height;
				SDL_GetWindowSize(_window, &width, &height);
				this->resizeWindow(width, height);
			}

			uint64_t now = SDL_GetPerformanceCounter();
			float deltaTime = (now - last) / (float)SDL_GetPerformanceFrequency();
			last = now;

			updateFPS(deltaTime);

			input->update();
			scene->update(deltaTime, *input, *renderer);
			renderer->update(_window);
		}
	}

	void Game::resizeWindow(uint32_t width, uint32_t height)
	{
		_windowWidth = width;
		_windowHeight = height;
		glViewport(0, 0, _windowWidth, _windowHeight);
	}

	void Game::updateFPS(float deltaTime)
	{
		_frameCount++;
		_fpsTimer += deltaTime;
		if (_fpsTimer >= _fpsDisplayRate)
		{
			if (displayFPS)
			{
				std::cout << "FPS: " << static_cast<float>(_frameCount) / _fpsDisplayRate << "\n";
			}
			_fpsTimer -= _fpsDisplayRate;
			_frameCount = 0;
		}
	}
}
