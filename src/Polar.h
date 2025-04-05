#pragma once

#ifdef POLAR_EXPORTS
#define POLAR_API __declspec(dllexport)
#else
#define POLAR_API __declspec(dllimport)
#endif

namespace polar {
	class Polar {
	public:
		POLAR_API int Initialize();
	};
}
