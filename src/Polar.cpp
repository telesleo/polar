#include "Polar.h"

#include <iostream>
#include "entt.hpp"
#include "SDL3/SDL.h"

namespace polar {
	int Polar::Initialize() {
		entt::registry registry;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		std::cout << "Hello, Polar!" << std::endl;
		return 0;
	}
}
