#include "input.h"

namespace polar
{
    Input::Input() : _quit(false), _windowResized(false)
    {

    }

	void Input::update()
	{
        _prevKeyState = _keyState;
        _prevMousePosition = _mousePosition;

        _axis = glm::vec2(0.0f);

        while (SDL_PollEvent(&_event))
        {
            switch (_event.type)
            {
            case SDL_EVENT_QUIT:
                _quit = true;
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                _windowResized = true;
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                handleKeyEvent(_event);
                break;


            case SDL_EVENT_MOUSE_MOTION:
                _mousePosition.x = _event.motion.x;
                _mousePosition.y = _event.motion.y;
                break;
            }
		}

        if (_keyState[SDLK_A] || _keyState[SDLK_LEFT])
        {
            _axis.x -= 1.0f;
        }
        if (_keyState[SDLK_D] || _keyState[SDLK_RIGHT])
        {
            _axis.x += 1.0f;
        }
        if (_keyState[SDLK_W] || _keyState[SDLK_UP])
        {
            _axis.y += 1.0f;
        }
        if (_keyState[SDLK_S] || _keyState[SDLK_DOWN])
        {
            _axis.y -= 1.0f;
        }
	}

    bool Input::quit() const
    {
        return _quit;
    }

    bool Input::windowResized() const
    {
        return _windowResized;
    }

    void Input::handleKeyEvent(const SDL_Event& event)
    {
        bool pressed = (event.type == SDL_EVENT_KEY_DOWN);
        SDL_Keycode key = event.key.key;
        _keyState[key] = pressed;
    }

    bool Input::isKeyPressed(SDL_Keycode key) const
    {
        auto keyState = _keyState.find(key);
        return keyState != _keyState.end() && keyState->second;
    }

    bool Input::wasKeyJustPressed(SDL_Keycode key) const
    {
        auto current = _keyState.find(key);
        auto previous = _prevKeyState.find(key);
        bool isDownNow = current != _keyState.end() && current->second;
        bool wasDownBefore = previous != _prevKeyState.end() && previous->second;
        return isDownNow && !wasDownBefore;
    }

    bool Input::wasKeyJustReleased(SDL_Keycode key) const
    {
        auto current = _keyState.find(key);
        auto previous = _prevKeyState.find(key);
        bool isDownNow = current != _keyState.end() && current->second;
        bool wasDownBefore = previous != _prevKeyState.end() && previous->second;
        return !isDownNow && wasDownBefore;
    }

    glm::vec2 Input::getMouseMovement() const
    {
        return glm::vec2
        (
            _mousePosition.x - _prevMousePosition.x,
            _mousePosition.y - _prevMousePosition.y
        );
    }

    const glm::vec2& Input::getAxis() const
    {
        return _axis;
    }
}
