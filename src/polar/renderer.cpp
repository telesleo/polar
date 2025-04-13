#include "renderer.h"

#include <glad/glad.h>
#include <cstdint>
#include <memory>
#include <iostream>
#include "render_object.h"

namespace polar
{
	Renderer::Renderer(SDL_Window* window) :
	_shader
	(
		Shader
		(
			"C:\\Users\\leona\\Projects\\cpp\\polar\\src\\polar\\shaders\\shader.vert",
			"C:\\Users\\leona\\Projects\\cpp\\polar\\src\\polar\\shaders\\shader.frag"
		)
	),
	_window(window),
	projectionView(glm::mat4(1.0f))
	{
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::update(SDL_Window* window)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (const auto& [key, renderObject] : _renderObjects)
		{
			_shader.use();
			_shader.setTransform(renderObject->transform);
			_shader.setTexture(renderObject->texture);
			glBindVertexArray(renderObject->vao);
			glBindBuffer(GL_ARRAY_BUFFER, renderObject->vbo);
			glDrawElements(GL_TRIANGLES, renderObject->indexCount, GL_UNSIGNED_INT, 0);
		}

		SDL_GL_SwapWindow(window);
	}

	WindowSize Renderer::getWindowSize() const
	{
		int width, height;
		SDL_GetWindowSize(_window, &width, &height);
		return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
	}

	uint32_t Renderer::add(
		float* vertices,
		uint32_t vertexSize,
		uint32_t* indices,
		uint32_t indexSize,
		Texture& texture,
		glm::mat4 transform
	)
	{
		uint32_t vao;
		uint32_t vbo;
		uint32_t ebo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		_renderObjects.emplace(vao, std::make_unique<RenderObject>(vao, vbo, ebo, indexSize, texture, transform));

		return vao;
	}

	void Renderer::updateTransform(uint32_t id, glm::mat4 transform)
	{
		_renderObjects[id]->transform = transform;
	}

	Texture& Renderer::getTexture(std::string path)
	{
		if (_textures.find(path) == _textures.end())
		{
			_textures.emplace(path, std::make_unique<Texture>(path.c_str()));
		}
		return *(_textures[path]);
	}
}
