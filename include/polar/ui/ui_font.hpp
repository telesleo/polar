#pragma once

#include <cstdint>
#include <vector>

#include "freetype/freetype.h"

namespace polar
{

struct ui_font
{
    std::vector<uint8_t> data;
    FT_Face face;
};

}
