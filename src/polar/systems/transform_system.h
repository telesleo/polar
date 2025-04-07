#pragma once

#include "../polar_api.h"

#include <entt.hpp>
#include "../scene.h"
#include "../system.h"
#include "../components/transform.h"

namespace polar
{
	class TransformSystem : public System
	{
	public:
		POLAR_API void update(entt::registry& registry) override;
	};
}
