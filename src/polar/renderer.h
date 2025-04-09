#pragma once

#include "polar_api.h"

#include <cstdint>
#include <SDL3/SDL.h>
#include "shader.h"

namespace polar
{
	class Renderer
	{
	public:
		POLAR_API Renderer();
		POLAR_API ~Renderer();
		POLAR_API void update(SDL_Window* window);
	private:
		uint32_t _vao;
		uint32_t _vbo;
		Shader _shader;
	};
}
