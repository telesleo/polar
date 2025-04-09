#pragma once

#include "polar_api.h"

#include <string>
#include <glad/glad.h>

namespace polar
{
	class Shader
	{
	public:
		POLAR_API Shader(const char* vertexPath, const char* fragmentPath);
		POLAR_API ~Shader();
		POLAR_API void use() const;
	private:
		uint32_t _id;
		std::string readFile(const char* filename);
		std::uint32_t compileCode(std::string code, GLenum shaderType);
	};
}
