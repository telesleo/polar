#include "renderer.h"

#include <glad/glad.h>
#include <cstdint>

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

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);

		glBindVertexArray(_vao);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
	}

	void Renderer::update(SDL_Window* window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		_shader.use();
		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}
}
