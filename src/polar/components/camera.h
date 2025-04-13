#pragma once

namespace polar
{
	struct Camera
	{
		int priority { 0 };
		float fieldOfView{ 45.0f };
		float near { 0.1f };
		float far { 100.0f };
	};
}
