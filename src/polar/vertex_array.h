#pragma once

#include <cstdint>

namespace polar
{
    struct VertexArray
    {
        uint32_t vao;
        uint32_t vbo;
        uint32_t ebo;
        uint32_t indexCount;
    };
}
