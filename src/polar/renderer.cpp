#include "renderer.h"

#include <glad/glad.h>
#include <cstdint>
#include <iostream>
#include "vertex_array.h"

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
		for (const VertexArray& vertexArray : _vertexArrays)
		{
			glDeleteVertexArrays(1, &vertexArray.vao);
			glDeleteBuffers(1, &vertexArray.vbo);
		}
	}

	void Renderer::update(SDL_Window* window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for (const VertexArray& vertexArray : _vertexArrays)
		{
			_shader.use();
			glBindVertexArray(vertexArray.vao);
			glBindBuffer(GL_ARRAY_BUFFER, vertexArray.vbo);
			glDrawElements(GL_TRIANGLES, vertexArray.indexCount, GL_UNSIGNED_INT, 0);
		}

		SDL_GL_SwapWindow(window);
	}

	void Renderer::add(float* vertices, uint32_t vertexSize, uint32_t* indices, uint32_t indexSize)
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		_vertexArrays.push_back({ vao, vbo, ebo, indexSize });
	}
}
