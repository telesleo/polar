#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <unordered_map>

#include "polar/renderer/hash_pair.hpp"
#include "polar/renderer/opengl/opengl_instance.hpp"
#include "polar/renderer/opengl/opengl_mesh.hpp"
#include "polar/renderer/renderer.hpp"

namespace polar
{

class opengl_renderer : public renderer
{
    public:
    opengl_renderer(SDL_Window* window);

    void resize(const int width, const int height) override;
    void set_clear_color(float r, float g, float b, float a) override;
    int get_uniform_location(program program, const std::string& name) override;

    void begin_frame() override;
    void end_frame() override;

    void clear(bool clear_color, bool clear_depth) override;

    void draw() override;

    texture create_texture(const image& image_data) override;
    program create_program(const std::string& vertex_source, const std::string& fragment_source) override;
    mesh create_mesh(const void* vertex_data, size_t vertex_count, const layout& vertex_layout, const void* index_data,
                     size_t index_count, index_type index_format) override;
    instance create_instance(const void* data, size_t count, const layout& layout) override;

    void update_instance(const instance instance, const void* data, size_t count) override;

    void destroy_texture(const texture texture) override;
    void destroy_program(const program program) override;
    void destroy_mesh(const mesh mesh) override;
    void destory_instance(const instance instance) override;

    void bind_texture(const texture texture, size_t slot) override;
    void bind_program(const program program) override;
    void bind_mesh(const mesh mesh) override;
    void bind_instance(const instance instance) override;

    void set_uniform_int(int location, int value) override;
    void set_uniform_float(int location, float value) override;
    void set_uniform_float2(int location, const float* value) override;
    void set_uniform_float3(int location, const float* value) override;
    void set_uniform_float4(int location, const float* value) override;
    void set_uniform_mat4(int location, const float* value) override;

    private:
    SDL_Window* _window;
    SDL_GLContext _context;

    mesh _current_mesh{0};
    instance _current_instance{0};
    GLuint _current_vao{0};

    texture _next_texture{1};
    program _next_program{1};
    mesh _next_mesh{1};
    instance _next_instance{1};

    std::unordered_map<texture, GLuint> _textures;
    std::unordered_map<program, GLuint> _programs;
    std::unordered_map<mesh, opengl_mesh> _meshes;
    std::unordered_map<instance, opengl_instance> _instances;

    std::unordered_map<unsigned int, std::unordered_map<std::string, GLint>> _uniform_locations;
    std::unordered_map<std::pair<mesh, instance>, GLuint> _vaos;

    GLuint get_vao(mesh mesh, instance instance);
};

}
