#pragma once

#include "polar_api.h"

#include "input.h"
#include <cstdint>

namespace polar
{
	class Game
	{
	public:
		POLAR_API Game(char* windowTitle, uint16_t windowWidth, uint16_t windowHeight);
		POLAR_API void start();
	private:
		char* _windowTitle;
		uint16_t _windowWidth;
		uint16_t _windowHeight;
		Input input;
	};
}
