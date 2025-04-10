#include "renderer.h"

#include <glad/glad.h>
#include <cstdint>
#include <iostream>
#include "render_object.h"

namespace polar
{
	Renderer::Renderer() : _shader
	(
		Shader
		(
			"C:\\Users\\leona\\Projects\\cpp\\polar\\src\\polar\\shaders\\shader.vert",
			"C:\\Users\\leona\\Projects\\cpp\\polar\\src\\polar\\shaders\\shader.frag"
		)
	)
	{
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	}

	Renderer::~Renderer()
	{
		for (const RenderObject& renderObject : _renderObjects)
		{
			glDeleteVertexArrays(1, &renderObject.vao);
			glDeleteBuffers(1, &renderObject.vbo);
		}
	}

	void Renderer::update(SDL_Window* window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for (const RenderObject& renderObject : _renderObjects)
		{
			_shader.use();
			renderObject.texture.use();
			glBindVertexArray(renderObject.vao);
			glBindBuffer(GL_ARRAY_BUFFER, renderObject.vbo);
			glDrawElements(GL_TRIANGLES, renderObject.indexCount, GL_UNSIGNED_INT, 0);
		}

		SDL_GL_SwapWindow(window);
	}

	void Renderer::add(float* vertices, uint32_t vertexSize, uint32_t* indices, uint32_t indexSize, Texture& texture)
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

		_renderObjects.push_back({ vao, vbo, ebo, indexSize, texture });
	}
}
