#include "render_object.h"

#include "glad/glad.h"

namespace polar
{
    RenderObject::RenderObject
    (
        uint32_t vao,
        uint32_t vbo,
        uint32_t ebo,
        uint32_t indexCount,
        std::string texturePath,
        const glm::mat4& transform
    ) : vao(vao), vbo(vbo), ebo(ebo), indexCount(indexCount), texturePath(texturePath), transform(transform)
    {

    }

    RenderObject::~RenderObject()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
}
