#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "polar/renderer/renderer.hpp"
#include "polar/renderer/renderer_types.hpp"
#include "polar/ui/ui_font.hpp"
#include "polar/ui/ui_font_instance.hpp"
#include "polar/ui/ui_types.hpp"

namespace polar
{

class ui_system
{
    public:
    ui_system(renderer& renderer);
    ~ui_system();

    void begin();
    void end();

    font_handle create_font(const std::vector<uint8_t>& font_data);
    void draw_text(font_handle font, uint16_t size, const std::string& text);

    void destroy_font(font_handle handle);

    private:
    FT_Library _freetype;
    renderer& _renderer;
    mesh _quad;

    std::unordered_map<font_handle, ui_font> _fonts;
    std::unordered_map<font_handle, std::unordered_map<uint16_t, ui_font_instance>> _font_instances;
    font_handle _next_font_handle{1};

    void create_font_instance(font_handle font, uint16_t size);
    void bake_glyph(font_handle font, uint16_t size, uint32_t codepoint);
};

}
