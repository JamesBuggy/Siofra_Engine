#pragma once

#include "math/vector2.hpp"

namespace siofraEngine::math
{
	class Vector3
	{
	public:
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } { };
		Vector3(Vector2 vector2, float z) : x{ vector2.x }, y{ vector2.y }, z{ z } { };

		Vector3 operator + (const Vector3& other) const noexcept { return Vector3{ x + other.x, y + other.y, z + other.z }; }
		Vector3 operator - (const Vector3& other) const noexcept { return Vector3{ x - other.x, y - other.y, z - other.z }; }
		Vector3 operator * (float scalar) const noexcept { return Vector3{ x * scalar, y * scalar, z * scalar }; }
		Vector3 operator / (float scalar) const { return Vector3{ x / scalar, y / scalar, z / scalar }; }

		void operator += (const Vector3& other) noexcept { x += other.x; y += other.y; z += other.z; }
		void operator -= (const Vector3& other) noexcept { x -= other.x; y -= other.y; z -= other.z; }
		void operator *= (float scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; }
		void operator /= (float scalar) { x /= scalar; y /= scalar; z /= scalar; }

		float x{ 0 };
		float y{ 0 };
		float z{ 0 };
	};
}