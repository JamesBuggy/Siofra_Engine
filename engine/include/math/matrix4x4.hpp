#pragma once

#include <algorithm>
#include <array>

namespace siofraEngine::math
{
	class Matrix4x4
	{
	public:
		Matrix4x4 operator + (const Matrix4x4& other) const noexcept
		{
			Matrix4x4 newMatrix{ };
			for (size_t i{ 0 }; i < elements.size(); ++i)
			{
				newMatrix.elements[i] = elements[i] + other.elements[i];
			}
			return newMatrix;
		}

		Matrix4x4 operator - (const Matrix4x4& other) const noexcept
		{
			Matrix4x4 newMatrix{ };
			for (size_t i{ 0 }; i < elements.size(); ++i)
			{
				newMatrix.elements[i] = elements[i] - other.elements[i];
			}
			return newMatrix;
		}

		Matrix4x4 operator * (const Matrix4x4& other) const noexcept
		{
			return multiply(other);
		}

		Matrix4x4 operator * (float scalar) const noexcept
		{
			Matrix4x4 newMatrix{ };
			for (size_t i{ 0 }; i < elements.size(); ++i)
			{
				newMatrix.elements[i] = elements[i] * scalar;
			}
			return newMatrix;
		}

		void operator += (const Matrix4x4& other) noexcept
		{
			for (size_t i{ 0 }; i < elements.size(); ++i)
			{
				elements[i] += other.elements[i];
			}
		}

		void operator -= (const Matrix4x4& other) noexcept
		{
			for (size_t i{ 0 }; i < elements.size(); ++i)
			{
				elements[i] -= other.elements[i];
			}
		}

		void operator *= (const Matrix4x4& other) noexcept
		{
			elements = std::move(multiply(other).elements);
		}

		void operator *= (float scalar) noexcept
		{
			for (size_t i{ 0 }; i < elements.size(); ++i)
			{
				elements[i] *= scalar;
			}
		}

		std::array<float, 16> elements{ };

	private:
		Matrix4x4 multiply(const Matrix4x4& other) const noexcept
		{
			Matrix4x4 newMatrix{ };
			for (size_t i{ 0 }; i < other.elements.size(); i += 4)
			{
				for (size_t j{ 0 }; j < 4; ++j)
				{
					newMatrix.elements[i + j] =
						other.elements[i + 0] * elements[j + 0] +
						other.elements[i + 1] * elements[j + 4] +
						other.elements[i + 2] * elements[j + 8] +
						other.elements[i + 3] * elements[j + 12];
				}
			}
			return newMatrix;
		}
	};
}