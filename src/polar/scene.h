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

		template <typename T, typename... Args>
		void addComponent(uint32_t entity, Args&&... args)
		{
			_registry.emplace<T>(static_cast<entt::entity>(entity), args...);
		}
	private:
		entt::registry _registry;
	};
}
