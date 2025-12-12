#pragma once

#include <glad/glad.h>

#include "polar/renderer/layout.hpp"

namespace polar
{

struct opengl_instance
{
    GLuint vbo{0};
    layout instance_layout;
    GLsizei count{0};
};

}
