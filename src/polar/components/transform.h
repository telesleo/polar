#pragma once

#include <glm/glm.hpp>

namespace polar
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::uvec3 scale;
	};
}
