#pragma once

#include "polar_api.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cstdint>
#include <vector>
#include "shader.h"
#include "vertex_array.h"

namespace polar
{
	class Renderer
	{
	public:
		POLAR_API Renderer();
		POLAR_API ~Renderer();
		POLAR_API void update(SDL_Window* window);
		POLAR_API void add(float* vertices, uint32_t vertexSize, uint32_t* indices, uint32_t indexSize);
	private:
		Shader _shader;
		std::vector<VertexArray> _vertexArrays;
	};
}
