#pragma once

#include "entt.hpp"

namespace polar
{
	class System
	{
	public:
		virtual void update(entt::registry& registry) = 0;

		template <typename... Components, typename Func>
		void action(entt::registry& registry, Func&& callback)
		{
			auto view = registry.view<Components...>();

			if constexpr (std::is_invocable_v<Func, uint32_t, Components&...>)
			{
				view.each
				(
					[&](entt::entity entity, Components&... components)
					{
						callback(static_cast<uint32_t>(entity), components...);
					}
				);
			}
			else
			{
				view.each(std::forward<Func>(callback));
			}
		}
	};
}
