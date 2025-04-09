#include "shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace polar
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath) : _id(0)
	{
        std::string vertexCode = readFile(vertexPath);
        uint32_t vertexId = compileCode(vertexCode, GL_VERTEX_SHADER);

        std::string fragmentCode = readFile(fragmentPath);
        uint32_t fragmentId = compileCode(fragmentCode, GL_FRAGMENT_SHADER);

        int success;
        _id = glCreateProgram();
        glAttachShader(_id, vertexId);
        glAttachShader(_id, fragmentId);
        glLinkProgram(_id);
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(_id, 512, NULL, infoLog);
            std::cout << "" << infoLog << std::endl;
        }
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
	}

    std::string Shader::readFile(const char* filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << "\"" << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    uint32_t Shader::compileCode(std::string code, GLenum shaderType)
    {
        const char* shaderSource = code.c_str();

        int success;
        uint32_t id = glCreateShader(shaderType);
        glShaderSource(id, 1, &shaderSource, NULL);
        glCompileShader(id);
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cout << "Failed to link shader program\n" << infoLog << std::endl;
        };

        return id;
    }

    Shader::~Shader()
    {
        glDeleteProgram(_id);
    }

    void Shader::use() const
    {
        glUseProgram(_id);
    }
}
