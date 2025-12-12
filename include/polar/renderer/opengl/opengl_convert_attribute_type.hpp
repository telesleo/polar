#pragma once

#include <glad/glad.h>

#include <stdexcept>

#include "polar/renderer/attribute.hpp"

namespace polar
{

static inline void opengl_convert_attribute_type(attribute_type type, GLint& out_count, GLenum& out_opengl_type)
{
    switch (type)
    {
        case attribute_type::float32:
            out_count = 1;
            out_opengl_type = GL_FLOAT;
            break;
        case attribute_type::float32x2:
            out_count = 2;
            out_opengl_type = GL_FLOAT;
            break;
        case attribute_type::float32x3:
            out_count = 3;
            out_opengl_type = GL_FLOAT;
            break;
        case attribute_type::float32x4:
            out_count = 4;
            out_opengl_type = GL_FLOAT;
            break;
        case attribute_type::uint32:
            out_count = 1;
            out_opengl_type = GL_INT;
            break;
        case attribute_type::uint32x2:
            out_count = 2;
            out_opengl_type = GL_INT;
            break;
        case attribute_type::uint32x3:
            out_count = 3;
            out_opengl_type = GL_INT;
            break;
        case attribute_type::uint32x4:
            out_count = 4;
            out_opengl_type = GL_INT;
            break;
        default:
            throw std::runtime_error("unsupported attribute type");
    }
}

}
