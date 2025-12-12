#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "polar/assets/image.hpp"
#include "polar/renderer/index_type.hpp"
#include "polar/renderer/layout.hpp"
#include "polar/renderer/renderer_types.hpp"

namespace polar
{

class renderer
{
    public:
    virtual ~renderer() = default;

    virtual void resize(const int width, const int height) = 0;
    virtual void set_clear_color(float r, float g, float b, float a) = 0;
    virtual int get_uniform_location(program program, const std::string& name) = 0;

    virtual void begin_frame() = 0;
    virtual void end_frame() = 0;

    virtual void clear(bool clear_color = true, bool clear_depth = true) = 0;

    virtual void draw() = 0;

    virtual texture create_texture(const image& image_data) = 0;
    virtual program create_program(const std::string& vertex_source, const std::string& fragment_source) = 0;
    virtual mesh create_mesh(const void* vertex_data, size_t vertex_count, const layout& vertex_layout,
                             const void* index_data, size_t index_count, index_type index_format) = 0;
    virtual instance create_instance(const void* data, size_t count, const layout& layout) = 0;

    virtual void update_instance(const instance instance, const void* data, size_t count) = 0;

    virtual void destroy_texture(const texture texture) = 0;
    virtual void destroy_program(const program program) = 0;
    virtual void destroy_mesh(const mesh mesh) = 0;
    virtual void destory_instance(const instance instance) = 0;

    virtual void bind_texture(const texture texture, size_t slot) = 0;
    virtual void bind_program(const program program) = 0;
    virtual void bind_mesh(const mesh mesh) = 0;
    virtual void bind_instance(const instance instance) = 0;

    virtual void set_uniform_int(int location, int value) = 0;
    virtual void set_uniform_float(int location, float value) = 0;
    virtual void set_uniform_float2(int location, const float* value) = 0;
    virtual void set_uniform_float3(int location, const float* value) = 0;
    virtual void set_uniform_float4(int location, const float* value) = 0;
    virtual void set_uniform_mat4(int location, const float* value) = 0;
};

}
