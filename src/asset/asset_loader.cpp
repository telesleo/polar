#define STB_IMAGE_IMPLEMENTATION

#include "polar/asset/asset_loader.hpp"

#include <stb_image.h>

#include <fstream>
#include <stdexcept>
#include <vector>

namespace polar
{

std::vector<uint8_t> asset_loader::load_binary(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("cannot open file: " + path);

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> data(size);
    file.read(reinterpret_cast<char*>(data.data()), size);

    return data;
}

std::string asset_loader::load_text(const std::string& path)
{
    auto bytes = load_binary(path);
    return std::string(bytes.begin(), bytes.end());
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
