#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>

namespace polar
{
	class Input
	{
	public:
		void update();
		void onKeyPressed(uint32_t key, std::function<void()> callback);
		void triggerKeyPress(uint32_t key);
	private:
		SDL_Event _event;
		std::unordered_map<uint32_t, std::vector<std::function<void()>>> _keyCallbacks;
	};
}
