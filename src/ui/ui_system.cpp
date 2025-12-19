#include "polar/ui/ui_system.hpp"

#include <cstdint>
#include <vector>

#include "polar/renderer/attribute_type.hpp"
#include "polar/renderer/index_type.hpp"
#include "polar/renderer/layout.hpp"
#include "polar/renderer/renderer.hpp"
#include "polar/ui/ui_font.hpp"
#include "polar/ui/ui_types.hpp"
#include "polar/ui/ui_vertex.hpp"

namespace polar
{

ui_system::ui_system(renderer& renderer) : _renderer(renderer)
{
    FT_Init_FreeType(&_freetype);

    std::vector<ui_vertex> vertices = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

    std::vector<uint16_t> indices = {0, 1, 2, 0, 2, 3};

    layout layout = {sizeof(ui_vertex), {{1, attribute_type::float32x2, 0}}};

    _quad = _renderer.create_mesh(vertices.data(), vertices.size(), layout, indices.data(), indices.size(),
                                  index_type::uint16);
}

ui_system::~ui_system()
{
    FT_Done_FreeType(_freetype);

    _renderer.destroy_mesh(_quad);
}

void begin() {}

void end() {}

font_handle ui_system::create_font(const std::vector<uint8_t>& font_data)
{
    font_handle handle = _next_font_handle++;

    ui_font font;

    font.data = font_data;
    FT_New_Memory_Face(_freetype, font.data.data(), static_cast<FT_Long>(font.data.size()), 0, &font.face);

    _fonts[handle] = font;

    return handle;
}

void ui_system::destroy_font(font_handle handle)
{
    auto it = _fonts.find(handle);
    if (it != _fonts.end())
    {
        FT_Done_Face(it->second.face);
        _fonts.erase(handle);
    }

    auto it_instance = _font_instances.find(handle);
    if (it_instance != _font_instances.end())
    {
        _font_instances.erase(it_instance);
    }
}

void ui_system::draw_text(font_handle font, uint16_t size, const std::string& text)
{
    auto font_it = _font_instances.find(font);
    if (font_it == _font_instances.end())
    {
        return;
    }

    auto& font_instances = font_it->second;

    auto instance_it = font_instances.find(size);
    if (instance_it == font_instances.end())
    {
        create_font_instance(font, size);

        instance_it = font_instances.find(size);
        if (instance_it == font_instances.end())
        {
            return;
        }
    }

    auto& font_instance = instance_it->second;

    _renderer.bind_program();
    _renderer.bind_mesh(_quad);
    _renderer.bind_instance();
    _renderer.draw();
}

void ui_system::create_font_instance(font_handle font, uint16_t size)
{
    auto font_it = _fonts.find(font);
    if (font_it == _fonts.end())
    {
        return;
    }

    auto& ui_font = font_it->second;

    FT_Error error = FT_Set_Pixel_Sizes(ui_font.face, 0, size);
    if (error)
    {
        return;
    }

    ui_font_instance instance;
    instance.size = size;

    instance.ascent = ui_font.face->size->metrics.ascender / 64.0f;
    instance.descent = ui_font.face->size->metrics.descender / 64.0f;
    instance.line_height = ui_font.face->size->metrics.height / 64.0f;

    image atlas;
    atlas.width = 1024;
    atlas.height = 1024;
    atlas.channels = 1;
    atlas.pixels.assign(1024 * 1024, 0);

    uint32_t pen_x = 0;
    uint32_t pen_y = 0;
    uint32_t row_height = 0;
    for (uint32_t cp = 0; cp < 256; ++cp)
    {
        if (FT_Load_Char(ui_font.face, cp, FT_LOAD_RENDER))
        {
            continue;
        }

        FT_GlyphSlot slot = ui_font.face->glyph;
        FT_Bitmap& bmp = slot->bitmap;

        if (bmp.width == 0 || bmp.rows == 0)
        {
            ui_glyph glyph{};
            glyph.advance = slot->advance.x / 64.0f;
            instance.glyphs.emplace(cp, glyph);
            continue;
        }

        if (pen_x + bmp.width > atlas.width)
        {
            pen_x = 0;
            pen_y += row_height;
            row_height = 0;
        }

        if (pen_y + bmp.rows > atlas.height)
        {
            break;
        }

        for (uint32_t row = 0; row < bmp.rows; ++row)
        {
            memcpy(&atlas.pixels[(pen_y + row) * atlas.width + pen_x], bmp.buffer + row * bmp.pitch, bmp.width);
        }

        ui_glyph glyph;
        glyph.advance = slot->advance.x / 64.0f;
        glyph.bearing_x = static_cast<float>(slot->bitmap_left);
        glyph.bearing_y = static_cast<float>(slot->bitmap_top);

        glyph.u0 = float(pen_x) / atlas.width;
        glyph.v0 = float(pen_y) / atlas.height;
        glyph.u1 = float(pen_x + bmp.width) / atlas.width;
        glyph.v1 = float(pen_y + bmp.rows) / atlas.height;

        instance.glyphs.emplace(cp, glyph);

        pen_x += bmp.width;
        row_height = std::max(row_height, bmp.rows);
    }

    instance.atlas = _renderer.create_texture(atlas);

    _font_instances[font].emplace(size, std::move(instance));
}

}
