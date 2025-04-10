#pragma once

#include <cstdint>
#include "texture.h"

namespace polar
{
    struct RenderObject
    {
        uint32_t vao;
        uint32_t vbo;
        uint32_t ebo;
        uint32_t indexCount;
        Texture& texture;
    };
}
