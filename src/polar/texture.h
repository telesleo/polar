#pragma once

#include "polar_api.h"

#include <cstdint>

namespace polar
{
	class Texture
	{
	public:
		POLAR_API Texture(char* path);
		POLAR_API ~Texture();
		POLAR_API void use() const;
	private:
		uint32_t _id;
	};
}
