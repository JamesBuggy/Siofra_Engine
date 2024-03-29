#pragma once

#include <cstdint>
#include <string>
#include "math/math.hpp"

namespace siofraEngine::core
{
	struct Transform
	{
		math::Vector3 position{ 0.0f, 0.0f, 0.0f };
	};

	struct Rotation
	{
		math::Vector3 angles{ 0.0f, 0.0f, 0.0f };
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
		math::Vector3 front{ 0.0f, 0.0f, 1.0f };
		math::Vector3 up{ 0.0f, 1.0f, 0.0f };
		math::Vector3 right{ -1.0f, 0.0f, 0.0f };
		math::Vector3 worldUp{ 0.0f, 1.0f, 0.0f };
		float yaw{ 90.0f };
		float pitch{ 0.0f };
	};

	struct AudioSource
	{
		std::string filename{ };
		bool play{ };
	};
}
