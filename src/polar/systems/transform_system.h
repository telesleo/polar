#pragma once

#include "../polar_api.h"

#include <entt.hpp>
#include "../system.h"
#include "../components/transform.h"

namespace polar
{
	class TransformSystem : public System
	{
	public:
		POLAR_API TransformSystem(entt::registry& registry);
		POLAR_API void update() override;
	};
}
