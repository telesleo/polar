#pragma once

#include <cstdint>
#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>
#include <glm/glm.hpp>

namespace polar
{
	class Input
	{
	public:
		Input();
		void update();
		bool quit() const;
		bool windowResized() const;
		bool isKeyPressed(SDL_Keycode key) const;
		bool wasKeyJustPressed(SDL_Keycode key) const;
		bool wasKeyJustReleased(SDL_Keycode key) const;
		const glm::vec2& getAxis() const;
		glm::vec2 getMouseMovement() const;
	private:
		SDL_Event _event;
		bool _quit;
		bool _windowResized;
		std::unordered_map<uint32_t, bool> _keyState;
		std::unordered_map<uint32_t, bool> _prevKeyState;
		glm::vec2 _axis;
		glm::vec2 _mousePosition;
		glm::vec2 _prevMousePosition;
		void handleKeyEvent(const SDL_Event& event);
	};
}
