#pragma once

#include <cstdint>

#include "polar/renderer/attribute_type.hpp"

namespace polar
{

struct attribute
{
    std::uint32_t location;
    attribute_type type;
    std::uint32_t offset;
};

}
