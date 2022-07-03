#pragma once

#include "math/vector2.hpp"

namespace siofraEngine::math
{
	class Vector3
	{
	public:
		Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } { };
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

		static float dotProduct(const Vector3& a, const Vector3& b) noexcept
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		static Vector3 crossProduct(const Vector3& a, const Vector3& b) noexcept
		{
			return Vector3{ a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x };
		}

		float magnitude() const noexcept
		{
			return sqrtf(magnitudeSquared());
		}

		float magnitudeSquared() const noexcept
		{
			return dotProduct(*this, *this);
		}

		void normalize() noexcept
		{
			float length = magnitude();
			if (length < FLT_EPSILON)
			{
				return;
			}
			*this /= length;
		}

		Vector3 normalized() const
		{
			Vector3 normalizedVector{ x, y, z };
			normalizedVector.normalize();
			return normalizedVector;
		}

		float x{ 0 };
		float y{ 0 };
		float z{ 0 };
	};
}