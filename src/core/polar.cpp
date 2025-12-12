#include "polar/core/polar.hpp"

#include "polar/core/frame_event.hpp"
#include "polar/renderer/opengl/opengl_renderer.hpp"

namespace polar
{

polar::polar(const std::string& title, const int width, const int height)
    : _window_title(title), _window_width(width), _window_height(height)
{
    _window = SDL_CreateWindow(_window_title.c_str(), _window_width, _window_height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);

    _renderer = std::make_unique<opengl_renderer>(_window);
}

renderer& polar::get_renderer() const
{
    return *_renderer;
}

int polar::get_window_width() const
{
    return _window_width;
}

int polar::get_window_height() const
{
    return _window_height;
}

void polar::run(const std::function<void(renderer&)>& on_start,
                const std::function<void(renderer&, frame_event)>& on_frame,
                const std::function<void(renderer&)>& on_end)
{
    uint64_t last_time = SDL_GetTicks();

    _running = true;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowWindow(_window);

    on_start(*_renderer);

    while (_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    _running = false;
                    break;

                case SDL_EVENT_WINDOW_RESIZED:
                {
                    int width = event.window.data1;
                    int height = event.window.data2;

                    _window_width = width;
                    _window_height = height;

                    if (_renderer)
                    {
                        _renderer->resize(width, height);
                    }

                    break;
                }

                default:
                    break;
            }
        }

        uint64_t now = SDL_GetTicks();
        float delta_time = (now - last_time) / 1000.0f;
        frame_event frame_event = {delta_time};
        last_time = now;

        _renderer->begin_frame();
        on_frame(*_renderer, frame_event);
        _renderer->end_frame();
    }

    on_end(*_renderer);

    SDL_DestroyWindow(_window);
    SDL_Quit();
}

}
