#pragma once

#include <math.h>
#include <algorithm>
#include <array>

namespace siofraEngine::math
{
	class Matrix4x4
	{
	public:
		Matrix4x4() = default;
		Matrix4x4(std::array<float, 16> elements) :
			elements{ std::move(elements) }
		{
		
		}

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

		/**
		 * @brief Create a perspective projection matrix
		 *
		 * @param fov The field of view, in the y direction, expressed in radians
		 * @param aspect The aspect ration determining the field of view in the x direction (width / height)
		 * @param near The distance, from the viewer, to the near clipping plane
		 * @param far The distance, from the viewer, to the far clipping plane
		 * @returns The perspective matrix, or an identity matrix in the case of invalid input
		 */
		static Matrix4x4 perspective(float fov, float aspect, float near, float far) noexcept
		{
			float frustumDepth = far - near;

			if (fov <= 0.0f || aspect == 0.0f || frustumDepth <= 0.0f || near <= 0.0f || far <= 0.0f)
			{
				return Matrix4x4
				{{
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
				}};
			}

			Matrix4x4 perpectiveMatrix{ };
			perpectiveMatrix.elements[5] = 1.0f / tanf(fov / 2);
			perpectiveMatrix.elements[0] = 1.0f * perpectiveMatrix.elements[5] / aspect;
			perpectiveMatrix.elements[10] = -((far + near) / frustumDepth);
			perpectiveMatrix.elements[11] = -1.0f;
			perpectiveMatrix.elements[14] = -((2.0f * far * near) / frustumDepth);
			return perpectiveMatrix;
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