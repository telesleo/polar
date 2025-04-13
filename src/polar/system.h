#pragma once

#include <entt.hpp>
#include "input.h"
#include "renderer.h"

namespace polar
{
	class System
	{
	public:
		virtual void start(entt::registry& registry, Input& input, Renderer& rendere) = 0;
		virtual void update(entt::registry& registry, Input& input, Renderer& renderer) = 0;
	};
}
