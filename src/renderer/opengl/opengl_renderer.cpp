#pragma once

#include "polar/renderer/opengl/opengl_renderer.hpp"

#include <stdexcept>

#include "polar/renderer/opengl/opengl_convert_attribute_type.hpp"
#include "polar/renderer/opengl/opengl_convert_index_type.hpp"

namespace polar
{

opengl_renderer::opengl_renderer(SDL_Window* window) : _window(window)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    if (!_window)
    {
        throw std::runtime_error("SDL_Window* is null");
    }

    _context = SDL_GL_CreateContext(_window);

    if (!_context)
    {
        throw std::runtime_error(std::string("failed to create OpenGL context: ") + SDL_GetError());
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        throw std::runtime_error("failed to initialize GLAD");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisable(GL_BLEND);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int width, height;
    SDL_GetWindowSizeInPixels(_window, &width, &height);
    glViewport(0, 0, width, height);

    SDL_GL_SetSwapInterval(0);
}

void opengl_renderer::resize(const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void opengl_renderer::set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

int opengl_renderer::get_uniform_location(program program, const std::string& name)
{
    auto program_it = _uniform_locations.find(program);

    if (program_it == _uniform_locations.end())
    {
        return -1;
    }

    auto& uniform_map = program_it->second;
    auto uniform_it = uniform_map.find(name);

    if (uniform_it == uniform_map.end())
    {
        return -1;
    }

    return uniform_it->second;
}

void opengl_renderer::begin_frame() {}

void opengl_renderer::end_frame()
{
    SDL_GL_SwapWindow(_window);
}

void opengl_renderer::clear(bool clear_color_buffer, bool clear_depth_buffer)
{
    GLbitfield flags = 0;
    if (clear_color_buffer)
    {
        flags |= GL_COLOR_BUFFER_BIT;
    }
    if (clear_depth_buffer)
    {
        flags |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(flags);
}

void opengl_renderer::draw()
{
    GLuint vao = get_vao(_current_mesh, _current_instance);

    if (vao != _current_vao)
    {
        glBindVertexArray(vao);
        _current_vao = vao;
    }

    if (_current_vao == 0)
    {
        return;
    }

    const opengl_mesh& opengl_mesh = _meshes[_current_mesh];

    if (_current_instance == 0)
    {
        glDrawElements(GL_TRIANGLES, opengl_mesh.index_count, opengl_mesh.index_type, nullptr);
    }
    else
    {
        const opengl_instance& opengl_instance = _instances[_current_instance];
        glDrawElementsInstanced(GL_TRIANGLES, opengl_mesh.index_count, opengl_mesh.index_type, nullptr,
                                static_cast<GLsizei>(opengl_instance.count));
    }
}

texture opengl_renderer::create_texture(const image& image)
{
    texture texture = _next_texture++;

    GLuint handle = 0;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    GLenum format;
    switch (image.channels)
    {
        case 1:
            format = GL_RED;
            break;
        case 2:
            format = GL_RG;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            throw std::runtime_error("unsupported number of channels in texture: " + std::to_string(image.channels));
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    _textures[texture] = handle;

    return texture;
};

program opengl_renderer::create_program(const std::string& vertex_source, const std::string& fragment_source)
{
    program program = _next_program++;

    auto compile_shader = [](GLenum type, const std::string& source) -> GLuint
    {
        GLuint handle = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(handle, 1, &src, nullptr);
        glCompileShader(handle);

        GLint success = 0;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLint logLen = 0;
            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLen);

            std::string log(logLen, '\0');
            glGetShaderInfoLog(handle, logLen, nullptr, log.data());

            glDeleteShader(handle);
            throw std::runtime_error("shader compile error: " + log);
        }

        return handle;
    };

    GLuint vertex = 0;
    GLuint fragment = 0;

    vertex = compile_shader(GL_VERTEX_SHADER, vertex_source);
    fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_source);

    GLuint handle = glCreateProgram();
    glAttachShader(handle, vertex);
    glAttachShader(handle, fragment);
    glLinkProgram(handle);

    GLint linked = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint logLength = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

        std::string log(logLength, '\0');
        glGetProgramInfoLog(handle, logLength, nullptr, log.data());

        glDeleteProgram(handle);
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        throw std::runtime_error("program link error: " + log);
    }

    glDetachShader(handle, vertex);
    glDetachShader(handle, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    _programs[program] = handle;

    GLint uniform_count = 0;
    glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &uniform_count);

    GLint max_len = 0;
    glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_len);
    std::vector<char> name(max_len);

    for (GLint i = 0; i < uniform_count; ++i)
    {
        GLsizei length = 0;
        GLint size = 0;
        GLenum type = 0;
        glGetActiveUniform(handle, i, max_len, &length, &size, &type, name.data());
        std::string uname(name.data(), length);
        GLint location = glGetUniformLocation(handle, uname.c_str());
        _uniform_locations[program][uname] = location;
    }

    return program;
};

mesh opengl_renderer::create_mesh(const void* vertex_data, size_t vertex_count, const layout& vertex_layout,
                                  const void* index_data, size_t index_count, index_type index_type)
{
    mesh mesh = _next_mesh++;

    opengl_mesh opengl_mesh;

    opengl_mesh.vertex_layout = vertex_layout;
    opengl_mesh.index_count = static_cast<GLsizei>(index_count);

    GLint index_stride = 1;

    opengl_convert_index_type(index_type, index_stride, opengl_mesh.index_type);

    glGenBuffers(1, &opengl_mesh.vbo);
    glGenBuffers(1, &opengl_mesh.ebo);

    glBindBuffer(GL_ARRAY_BUFFER, opengl_mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * opengl_mesh.vertex_layout.stride, vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl_mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, opengl_mesh.index_count * index_stride, index_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    _meshes[mesh] = opengl_mesh;

    return mesh;
}

instance opengl_renderer::create_instance(const void* data, size_t count, const layout& layout)
{
    instance instance = _next_instance++;

    opengl_instance opengl_instance;

    opengl_instance.count = count;
    opengl_instance.instance_layout = layout;

    glGenBuffers(1, &opengl_instance.vbo);

    glBindBuffer(GL_ARRAY_BUFFER, opengl_instance.vbo);
    glBufferData(GL_ARRAY_BUFFER, count * opengl_instance.instance_layout.stride, data, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _instances[instance] = opengl_instance;

    return instance;
}

void opengl_renderer::update_instance(const instance instance, const void* data, size_t count)
{
    auto it = _instances.find(instance);
    if (it == _instances.end())
    {
        throw std::runtime_error("instance not found");
    }

    opengl_instance& opengl_instance = it->second;

    opengl_instance.count = count;

    glBindBuffer(GL_ARRAY_BUFFER, opengl_instance.vbo);
    glBufferData(GL_ARRAY_BUFFER, count * opengl_instance.instance_layout.stride, data, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _instances[instance] = opengl_instance;
}

void opengl_renderer::destroy_texture(const texture texture)
{
    auto it = _textures.find(texture);
    if (it == _textures.end())
    {
        return;
    }

    GLuint handle = it->second;
    glDeleteTextures(1, &handle);

    _textures.erase(it);
}

void opengl_renderer::destroy_program(const program program)
{
    auto it = _programs.find(program);
    if (it == _programs.end())
    {
        return;
    }

    GLuint handle = it->second;
    glDeleteProgram(handle);

    _programs.erase(it);
    _uniform_locations.erase(program);
}

void opengl_renderer::destroy_mesh(const mesh mesh)
{
    auto it = _meshes.find(mesh);
    if (it == _meshes.end())
    {
        return;
    }

    opengl_mesh& opengl_mesh = it->second;

    glDeleteBuffers(1, &opengl_mesh.vbo);
    glDeleteBuffers(1, &opengl_mesh.ebo);

    _meshes.erase(it);
}

void opengl_renderer::destory_instance(const instance instance)
{
    auto it = _instances.find(instance);
    if (it == _instances.end())
    {
        return;
    }

    opengl_instance& opengl_instance = it->second;

    glDeleteBuffers(1, &opengl_instance.vbo);

    _instances.erase(it);
}

void opengl_renderer::bind_texture(const texture texture, size_t slot)
{
    glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(slot));
    glBindTexture(GL_TEXTURE_2D, _textures.at(texture));
}

void opengl_renderer::bind_program(const program program)
{
    glUseProgram(_programs.at(program));
}

void opengl_renderer::bind_mesh(const mesh mesh)
{
    _current_mesh = mesh;
}

void opengl_renderer::bind_instance(const instance instance)
{
    _current_instance = instance;
}

void opengl_renderer::set_uniform_int(int location, int value)
{
    glUniform1i(location, value);
}

void opengl_renderer::set_uniform_float(int location, float value)
{
    glUniform1f(location, value);
}

void opengl_renderer::set_uniform_float2(int location, const float* value)
{
    glUniform2fv(location, 1, value);
}

void opengl_renderer::set_uniform_float3(int location, const float* value)
{
    glUniform3fv(location, 1, value);
}

void opengl_renderer::set_uniform_float4(int location, const float* value)
{
    glUniform4fv(location, 1, value);
}

void opengl_renderer::set_uniform_mat4(int location, const float* value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

GLuint opengl_renderer::get_vao(mesh mesh, instance instance)
{
    if (mesh == 0)
    {
        return 0;
    }

    auto vao_it = _vaos.find(std::pair(mesh, instance));
    if (vao_it != _vaos.end())
    {
        return vao_it->second;
    }

    auto mesh_it = _meshes.find(mesh);
    if (mesh_it == _meshes.end())
    {
        throw std::runtime_error("mesh not found");
    }

    const opengl_mesh& opengl_mesh = mesh_it->second;

    GLuint vao = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, opengl_mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl_mesh.ebo);

    for (const attribute& attribute : opengl_mesh.vertex_layout.attributes)
    {
        glEnableVertexAttribArray(attribute.location);

        GLint count;
        GLenum type;
        opengl_convert_attribute_type(attribute.type, count, type);

        if (type == GL_INT)
        {
            glVertexAttribIPointer(attribute.location, count, type, opengl_mesh.vertex_layout.stride,
                                   reinterpret_cast<const void*>(static_cast<intptr_t>(attribute.offset)));
        }
        else
        {
            glVertexAttribPointer(attribute.location, count, type, GL_FALSE, opengl_mesh.vertex_layout.stride,
                                  reinterpret_cast<const void*>(static_cast<intptr_t>(attribute.offset)));
        }
    }

    if (instance != 0)
    {
        auto instance_it = _instances.find(instance);
        if (instance_it == _instances.end())
        {
            throw std::runtime_error("instance not found");
        }

        const opengl_instance& opengl_instance = instance_it->second;

        glBindBuffer(GL_ARRAY_BUFFER, opengl_instance.vbo);

        for (const attribute& attribute : opengl_instance.instance_layout.attributes)
        {
            glEnableVertexAttribArray(attribute.location);

            GLint count;
            GLenum type;
            opengl_convert_attribute_type(attribute.type, count, type);

            if (type == GL_INT)
            {
                glVertexAttribIPointer(attribute.location, count, type, opengl_instance.instance_layout.stride,
                                       reinterpret_cast<const void*>(static_cast<intptr_t>(attribute.offset)));
            }
            else
            {
                glVertexAttribPointer(attribute.location, count, type, GL_FALSE, opengl_instance.instance_layout.stride,
                                      reinterpret_cast<const void*>(static_cast<intptr_t>(attribute.offset)));
            }

            glVertexAttribDivisor(attribute.location, 1);
        }
    }

    glBindVertexArray(0);

    _vaos[std::pair(mesh, instance)] = vao;

    return vao;
}

}
