#include "input.h"

namespace polar
{
    void Input::onKeyPressed(uint32_t key, std::function<void()> callback)
    {
        _keyCallbacks[key].push_back(std::move(callback));
    }

    void Input::triggerKeyPress(uint32_t key)
    {
        if (_keyCallbacks.count(key))
        {
            for (auto& callback : _keyCallbacks[key])
            {
                callback();
            }
        }
    }

	void Input::update()
	{
		while (SDL_PollEvent(&_event))
		{
            if (_event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                
            }
            triggerKeyPress(_event.type);
		}
	}
}
