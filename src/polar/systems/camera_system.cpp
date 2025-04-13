#include "camera_system.h"

#include <iostream>
#include <glm/glm.hpp>
#include "../components/transform.h"
#include "../components/camera.h"
#include "../window_size.h"

namespace polar
{
	void CameraSystem::start(entt::registry& registry, Input& input, Renderer& renderer)
	{
		registry.sort<Camera>
		(
			[](const Camera& a, const Camera& b)
			{
				return a.priority > b.priority;
			}
		);
	}

	void CameraSystem::update
	(
		float deltaTime,
		entt::registry& registry,
		Input& input,
		Renderer& renderer
	)
	{
		auto view = registry.view<Transform, Camera>();

		if (view.size_hint() <= 0)
		{
			return;
		}
		
		view.use<Camera>();
		
		entt::entity entity = *view.begin();
		Transform& transform = view.get<Transform>(entity);
		Camera& camera = view.get<Camera>(entity);

		glm::mat4 worldMatrix = glm::translate(glm::mat4(1.0f), transform.position);
		worldMatrix = glm::rotate(worldMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		worldMatrix = glm::rotate(worldMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		worldMatrix = glm::rotate(worldMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 viewMatrix = glm::inverse(worldMatrix);

		WindowSize windowSize = renderer.getWindowSize();
		glm::mat4 projectionMatrix = glm::perspective
		(
			glm::radians(camera.fieldOfView),
			(float)windowSize.width / (float)windowSize.height,
			camera.near,
			camera.far
		);
		renderer.projectionView = projectionMatrix * viewMatrix;
	}
}
