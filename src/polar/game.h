#pragma once

#include "polar_api.h"

#include <cstdint>
#include <memory>
#include "input.h"
#include "renderer.h"
#include "scene.h";

namespace polar
{
	class Game
	{
	public:
		POLAR_API Game(char* windowTitle, uint16_t windowWidth, uint16_t windowHeight);
		POLAR_API ~Game();
		POLAR_API void start();
		POLAR_API void resizeWindow(uint32_t width, uint32_t height);
		std::unique_ptr<Input> input;
		std::unique_ptr<Scene> scene;
		std::unique_ptr<Renderer> renderer;
		bool displayFPS;
	private:
		char* _windowTitle;
		uint16_t _windowWidth;
		uint16_t _windowHeight;
		SDL_Window* _window;
		SDL_GLContext _context;
		bool _running;
		float _deltaTime;
		uint64_t _last;
		uint32_t _frameCount;
		float _fpsTimer;
		float _fpsDisplayRate;

		void updateDeltaTime();
		void updateFPS();
	};
}
