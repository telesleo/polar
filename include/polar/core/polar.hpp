#pragma once

#include <SDL3/SDL.h>

#include <functional>
#include <memory>
#include <string>

#include "polar/core/frame_event.hpp"
#include "polar/renderer/renderer.hpp"

namespace polar
{

class polar
{
    public:
    polar(const std::string& title, const int width, const int height);

    renderer& get_renderer() const;
    int get_window_width() const;
    int get_window_height() const;

    void run(
        const std::function<void(renderer&)>& on_start = [](renderer&) {},
        const std::function<void(renderer&, frame_event)>& on_frame = [](renderer&, frame_event) {},
        const std::function<void(renderer&)>& on_end = [](renderer&) {});

    private:
    bool _running{false};
    std::string _window_title;
    int _window_width;
    int _window_height;
    SDL_Window* _window;
    std::unique_ptr<renderer> _renderer;
};

}
