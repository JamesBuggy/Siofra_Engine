#pragma once

#include "math/vector3.hpp"

namespace siofraEngine::math
{
	class Vector4
	{
	public:
		Vector4() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 0.0f } { };
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

		static float dotProduct(const Vector4& a, const Vector4& b) noexcept
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
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

		Vector4 normalized() const
		{
			Vector4 normalizedVector{ x, y, z, w };
			normalizedVector.normalize();
			return normalizedVector;
		}

		float x{ 0 };
		float y{ 0 };
		float z{ 0 };
		float w{ 0 };
	};
}
