#pragma once

#include "entt.hpp"

namespace polar
{
	class System
	{
	public:
		System(entt::registry& registry);
		virtual void update() = 0;

		template <typename... Components, typename Func>
		void action(Func&& callback)
		{
			auto view = _registry.view<Components...>();

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
	private:
		entt::registry& _registry;
	};
}
