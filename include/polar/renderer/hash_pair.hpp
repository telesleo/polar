#pragma once

#include <functional>
#include <utility>

#include "polar/renderer/renderer_types.hpp"

namespace std
{

template <>
struct hash<std::pair<polar::mesh, polar::instance>>
{
    size_t operator()(const std::pair<polar::mesh, polar::instance>& p) const noexcept
    {
        size_t h1 = std::hash<polar::mesh>{}(p.first);
        size_t h2 = std::hash<polar::instance>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

}
