#pragma once

#include <glad/glad.h>

#include <stdexcept>

#include "polar/renderer/index_type.hpp"

namespace polar
{

static inline void opengl_convert_index_type(index_type type, GLsizei& out_size, GLenum& out_opengl_type)
{
    switch (type)
    {
        case index_type::uint8:
            out_opengl_type = GL_UNSIGNED_BYTE;
            out_size = 1;
            break;
        case index_type::uint16:
            out_opengl_type = GL_UNSIGNED_SHORT;
            out_size = 2;
            break;
        case index_type::uint32:
            out_opengl_type = GL_UNSIGNED_INT;
            out_size = 4;
            break;
        default:
            throw std::runtime_error("invalid index_type");
    }
}

}
