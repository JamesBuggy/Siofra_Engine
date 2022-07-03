#pragma once

#include "math/vector3.hpp"

namespace siofraEngine::math
{
	class Vector4
	{
	public:
		Vector4(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } { };
		Vector4(Vector3 vector3, float w) : x{ vector3.x }, y{ vector3.y }, z{ vector3.z }, w{ w } { };

		Vector4 operator + (const Vector4& other) const noexcept { return Vector4{ x + other.x, y + other.y, z + other.z, w + other.w }; }
		Vector4 operator - (const Vector4& other) const noexcept { return Vector4{ x - other.x, y - other.y, z - other.z, w - other.w }; }
		Vector4 operator * (float scalar) const noexcept { return Vector4{ x * scalar, y * scalar, z * scalar, w * scalar }; }
		Vector4 operator / (float scalar) const { return Vector4{ x / scalar, y / scalar, z / scalar, w / scalar }; }

		void operator += (const Vector4& other) noexcept { x += other.x; y += other.y; z += other.z; w += other.w; }
		void operator -= (const Vector4& other) noexcept { x -= other.x; y -= other.y; z -= other.z; w -= other.w; }
		void operator *= (float scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; w *= scalar; }
		void operator /= (float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; }

		static float dotProduct(const Vector4& a, const Vector4& b) noexcept { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w); }

		float x{ 0 };
		float y{ 0 };
		float z{ 0 };
		float w{ 0 };
	};
}
