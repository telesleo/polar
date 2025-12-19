#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "polar/data/image.hpp"

namespace polar
{

class asset_loader
{
    public:
    static std::vector<uint8_t> load_binary(const std::string& path);
    static std::string load_text(const std::string& path);
    static image load_image(const std::string& path, bool flip_vertically = true);
};

}
