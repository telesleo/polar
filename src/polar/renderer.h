#pragma once

#include "polar_api.h"

#include <SDL3/SDL.h>

namespace polar
{
	class Renderer
	{
	public:
		POLAR_API Renderer();
		void update(SDL_Window* window);
	};
}
