#pragma once

#include "polar_api.h"

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "render_object.h"
#include "texture.h"
#include "window_size.h"

namespace polar
{
	class Renderer
	{
	public:
		POLAR_API Renderer(SDL_Window* window);
		POLAR_API WindowSize getWindowSize() const;
		POLAR_API void update(SDL_Window* window);
		POLAR_API uint32_t add
		(
			float* vertices,
			uint32_t vertexSize,
			uint32_t* indices,
			uint32_t indexSize,
			Texture& texture,
			glm::mat4 transform
		);
		POLAR_API void updateTransform(uint32_t id, glm::mat4 transform);
		POLAR_API Texture& getTexture(std::string path);
		glm::mat4 projectionView;
	private:
		SDL_Window* _window;
		Shader _shader;
		std::map<uint32_t, std::unique_ptr<RenderObject>> _renderObjects;
		std::map<std::string, std::unique_ptr<Texture>> _textures;
	};
}
