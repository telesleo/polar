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

		_last = SDL_GetPerformanceCounter();

		scene->start(*input, *renderer);

		while (_running)
		{
			updateDeltaTime();
			if (displayFPS)
			{
				updateFPS();
			}

			input->update();

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

			scene->update(_deltaTime, *input, *renderer);
			renderer->update(_window);
		}
	}

	void Game::resizeWindow(uint32_t width, uint32_t height)
	{
		_windowWidth = width;
		_windowHeight = height;
		glViewport(0, 0, _windowWidth, _windowHeight);
	}

	void Game::updateDeltaTime()
	{
		uint64_t now = SDL_GetPerformanceCounter();
		_deltaTime = (now - _last) / (float)SDL_GetPerformanceFrequency();
		_last = now;
	}

	void Game::updateFPS()
	{
		_frameCount++;
		_fpsTimer += _deltaTime;
		if (_fpsTimer >= _fpsDisplayRate)
		{
			uint32_t fps = static_cast<float>(_frameCount) / _fpsTimer;
			std::cout << "FPS: " << fps << "\n";
			_fpsTimer = 0;
			_frameCount = 0;
		}
	}
}
