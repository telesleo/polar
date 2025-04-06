#pragma once

#include "entt.hpp"

namespace polar
{
	class System
	{
	public:
		System(entt::registry& registry);
		virtual void update() = 0;
	protected:
		entt::registry& _registry;
	};
}
