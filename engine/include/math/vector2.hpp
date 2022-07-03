#pragma once

namespace siofraEngine::math
{
	class Vector2
	{
	public:
		Vector2(float x, float y) : x{ x }, y{ y } { };

		Vector2 operator + (const Vector2& other) const noexcept { return Vector2{ x + other.x, y + other.y }; }
		Vector2 operator - (const Vector2& other) const noexcept { return Vector2{ x - other.x, y - other.y }; }
		Vector2 operator * (float scalar) const noexcept { return Vector2{ x * scalar, y * scalar }; }
		Vector2 operator / (float scalar) const { return Vector2{ x / scalar, y / scalar }; }

		void operator += (const Vector2& other) noexcept { x += other.x; y += other.y; }
		void operator -= (const Vector2& other) noexcept { x -= other.x; y -= other.y; }
		void operator *= (float scalar) noexcept { x *= scalar; y *= scalar; }
		void operator /= (float scalar) { x /= scalar; y /= scalar; }

		float x{ 0 };
		float y{ 0 };
	};
}