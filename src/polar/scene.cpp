#include "scene.h"

namespace polar
{
	uint32_t Scene::addEntity()
	{
		return static_cast<uint32_t>(_registry.create());
	}
}
