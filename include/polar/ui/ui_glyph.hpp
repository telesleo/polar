#pragma once

#include <cstdint>

namespace polar
{

struct ui_glyph
{
    uint32_t codepoint;
    float advance;
    float bearing_x;
    float bearing_y;
    float width;
    float height;
    float u0, v0, u1, v1;
};

}
