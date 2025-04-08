#pragma once

#include "polar_api.h"

#include <cstdint>
#include <SDL3/SDL.h>

namespace polar
{
	class Renderer
	{
	public:
		POLAR_API Renderer();
		POLAR_API ~Renderer();
		void update(SDL_Window* window);
	private:
		uint32_t _vao;
		uint32_t _vbo;
		uint32_t _shaderProgram;
	};
}
