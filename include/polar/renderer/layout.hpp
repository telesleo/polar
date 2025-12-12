#pragma once

#include <cstdint>
#include <vector>

#include "polar/renderer/attribute.hpp"

namespace polar
{

struct layout
{
    std::uint32_t stride;
    std::vector<attribute> attributes;
};

}
