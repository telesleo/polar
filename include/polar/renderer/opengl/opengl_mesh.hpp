#pragma once

#include <glad/glad.h>

#include "polar/renderer/layout.hpp"

namespace polar
{

struct opengl_mesh
{
    GLuint vbo{0};
    GLuint ebo{0};
    layout vertex_layout;
    GLsizei index_count{0};
    GLenum index_type{0};
};

}
