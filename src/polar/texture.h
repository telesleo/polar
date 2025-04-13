#pragma once

#include "polar_api.h"

#include <cstdint>

namespace polar
{
	class Texture
	{
	public:
		POLAR_API Texture(const char* path);
		POLAR_API ~Texture();
		POLAR_API uint32_t getId() const;
	private:
		uint32_t _id;
	};
}
