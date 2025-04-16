#pragma once

#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include "texture.h"

namespace polar
{
    class RenderObject
    {
    public:
        uint32_t vao;
        uint32_t vbo;
        uint32_t ebo;
        uint32_t indexCount;
        std::string texturePath;
        glm::mat4 transform;
        RenderObject
        (
            uint32_t vao,
            uint32_t vbo,
            uint32_t ebo,
            uint32_t indexCount,
            std::string texturePath,
            const glm::mat4& transform
        );
        ~RenderObject();
    };
}
