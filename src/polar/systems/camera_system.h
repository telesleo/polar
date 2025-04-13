#pragma once

#include "../polar_api.h"

#include "../system.h"

namespace polar
{
	class CameraSystem : public System
	{
	public:
		POLAR_API void start(entt::registry& registry, Input& input, Renderer& renderer) override;
		POLAR_API void update
		(
			float deltaTime,
			entt::registry& registry,
			Input& input,
			Renderer& renderer
		) override;
	};
}
