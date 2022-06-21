#pragma once

#include <cstdint>
#include <string>
#include "math/math.hpp"

namespace siofraEngine::core
{
	struct Transform
	{
		Vector3 position{ };
	};

	struct Rotation
	{
		float angle{ };
	};

	struct ModelUpdated { };
	struct Model
	{
		std::string filename{ };
	};

	struct MaterialUpdated { };
	struct Material
	{
		std::string filename{ };
	};

	struct Camera
	{
		Vector3 front{ 0.0f, 0.0f, 1.0f };
		Vector3 up{ 0.0f, 1.0f, 0.0f };
		Vector3 right{ -1.0f, 0.0f, 0.0f };
		Vector3 worldUp{ 0.0f, 1.0f, 0.0f };
		float yaw{ 90.0f };
		float pitch{ 0.0f };
	};
}
