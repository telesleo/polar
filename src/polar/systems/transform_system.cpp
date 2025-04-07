#include "transform_system.h"

#include <iostream>

namespace polar
{
	void TransformSystem::update(entt::registry& registry)
	{
		action<Transform>(registry, [](Transform& transform)
			{
				transform.positionX += 1;
				std::cout << "PositionX: " << transform.positionX << " PositionY: " << transform.positionY << std::endl;
			}
		);
	}
}
