#include "scene.h"

namespace polar
{
	uint32_t Scene::addEntity()
	{
		return static_cast<uint32_t>(_registry.create());
	}

	void Scene::start(Input& input, Renderer& renderer)
	{
		for (auto& system : _systems)
		{
			system->start(_registry, input, renderer);
		}
	}

	void Scene::update(float deltaTime, Input& input, Renderer& renderer)
	{
		for (auto& system : _systems)
		{
			system->update(deltaTime, _registry, input, renderer);
		}
	}
}
