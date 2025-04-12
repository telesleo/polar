#pragma once

#include "polar_api.h"

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "texture.h"

namespace polar
{
	class Shader
	{
	public:
		POLAR_API Shader(const char* vertexPath, const char* fragmentPath);
		POLAR_API ~Shader();
		POLAR_API void use() const;
		POLAR_API void setTransform(glm::mat4 transform);
		POLAR_API void Shader::setTexture(Texture& texture);
	private:
		uint32_t _id;
		std::string readFile(const char* filename);
		std::uint32_t compileCode(std::string code, GLenum shaderType);
	};
}
