#pragma once

#include <unordered_map>

#include "polar/renderer/renderer_types.hpp"
#include "polar/ui/ui_glyph.hpp"

namespace polar
{

struct ui_font_instance
{
    uint16_t size;
    float ascent;
    float descent;
    float line_height;
    std::unordered_map<uint32_t, ui_glyph> glyphs;
    texture atlas;
};

}
