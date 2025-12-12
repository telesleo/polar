#define STB_IMAGE_IMPLEMENTATION

#include "polar/assets/asset_loader.hpp"

#include <stb_image.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace polar
{

std::string asset_loader::load_file(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("cannot open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

image asset_loader::load_image(const std::string& path, bool flip_vertically)
{
    stbi_set_flip_vertically_on_load(flip_vertically);

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        throw std::runtime_error("failed to load image " + path + ": " + stbi_failure_reason());
    }

    std::vector<unsigned char> pixels(data, data + width * height * channels);

    stbi_image_free(data);

    return {width, height, channels, std::move(pixels)};
}

}
