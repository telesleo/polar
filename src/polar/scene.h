#pragma once

#include "polar_api.h"

#include <cstdint>
#include <entt.hpp>
#include "system.h"

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

		template <typename T>
		void addSystem()
		{
			T system(_registry);
			_systems.push_back(std::make_unique<T>(_registry));
		}

		POLAR_API void update();
	private:
		entt::registry _registry;
		std::vector<std::unique_ptr<System>> _systems;
	};
}
