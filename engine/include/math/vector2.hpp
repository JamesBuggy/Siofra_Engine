#pragma once

#include <math.h>
#include <float.h>

namespace siofraEngine::math
{
	class Vector2
	{
	public:
		Vector2() : x{ 0.0f }, y{ 0.0f } { };
		Vector2(float x, float y) : x{ x }, y{ y } { };

		Vector2 operator + (const Vector2& other) const noexcept { return Vector2{ x + other.x, y + other.y }; }
		Vector2 operator - (const Vector2& other) const noexcept { return Vector2{ x - other.x, y - other.y }; }
		Vector2 operator * (float scalar) const noexcept { return Vector2{ x * scalar, y * scalar }; }
		Vector2 operator / (float scalar) const { return Vector2{ x / scalar, y / scalar }; }

		void operator += (const Vector2& other) noexcept { x += other.x; y += other.y; }
		void operator -= (const Vector2& other) noexcept { x -= other.x; y -= other.y; }
		void operator *= (float scalar) noexcept { x *= scalar; y *= scalar; }
		void operator /= (float scalar) { x /= scalar; y /= scalar; }

		static float dotProduct(const Vector2& a, const Vector2& b) noexcept
		{
			return (a.x * b.x) + (a.y * b.y);
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

		Vector2 normalized() const
		{
			Vector2 normalizedVector{ x, y };
			normalizedVector.normalize();
			return normalizedVector;
		}

		float x{ 0 };
		float y{ 0 };
	};
}