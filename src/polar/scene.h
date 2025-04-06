#pragma once

#include "polar_api.h"

#include <cstdint>
#include <entt.hpp>

namespace polar
{
	class Scene
	{
	public:
		POLAR_API uint32_t addEntity();
	private:
		entt::registry _registry;
	};
}
