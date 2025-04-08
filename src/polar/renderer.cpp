#include "renderer.h"

#include <glad/glad.h>

#include <iostream>

namespace polar
{
	Renderer::Renderer()
	{
		glClearColor(0.7f, 0.9f, 0.9f, 1.0f);
	}

	void Renderer::update(SDL_Window* window)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}
}
