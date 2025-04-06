#include "transform_system.h"

#include <iostream>

namespace polar
{
	TransformSystem::TransformSystem(entt::registry& registry): System(registry) {}

	void TransformSystem::update()
	{
		action<Transform>([](Transform& transform)
			{
				transform.positionX += 1;
				std::cout << "PositionX: " << transform.positionX << " PositionY: " << transform.positionY << std::endl;
			}
		);
	}
}
