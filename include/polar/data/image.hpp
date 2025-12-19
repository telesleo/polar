#pragma once

#include <vector>

namespace polar
{

struct image
{
    int width;
    int height;
    int channels;
    std::vector<unsigned char> pixels;
};

}
