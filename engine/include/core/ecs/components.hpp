#pragma once

#include <cstdint>
#include <string>

namespace siofraEngine::core
{
	struct Transform
	{
		float x{ };
		float y{ };
		float z{ };
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
	
	};
}
