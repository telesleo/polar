#pragma once

#include <string>

#include "polar/assets/image.hpp"

namespace polar
{

class asset_loader
{
    public:
    static std::string load_file(const std::string& path);
    static image load_image(const std::string& path, bool flip_vertically = true);
};

}
