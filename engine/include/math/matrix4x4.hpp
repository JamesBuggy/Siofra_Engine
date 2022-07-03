#pragma once

#include <math.h>
#include <algorithm>
#include <array>
#include "math/vector3.hpp"

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
				return Matrix4x4::identity();
			}

			Matrix4x4 perpectiveMatrix{ };
			perpectiveMatrix.elements[5] = 1.0f / tanf(fov / 2);
			perpectiveMatrix.elements[0] = 1.0f * perpectiveMatrix.elements[5] / aspect;
			perpectiveMatrix.elements[10] = -((far + near) / frustumDepth);
			perpectiveMatrix.elements[11] = -1.0f;
			perpectiveMatrix.elements[14] = -((2.0f * far * near) / frustumDepth);
			return perpectiveMatrix;
		}

		/**
		 * @brief Create a view matrix
		 *
		 * @param eye The camera position
		 * @param target The position to which the camera is orientated to look at
		 * @param up Normalized up vector
		 * @returns The view matrix
		 */
		static Matrix4x4 lookAt(Vector3 eye, Vector3 target, Vector3 up) noexcept
		{
			Vector3 zAxis = (eye - target).normalized();
			Vector3 xAxis = Vector3::crossProduct(up, zAxis).normalized();
			Vector3 yAxis = Vector3::crossProduct(zAxis, xAxis);

			Matrix4x4 viewMatrix
			{{
				xAxis.x, yAxis.x, zAxis.x, 0,
				xAxis.y, yAxis.y, zAxis.y, 0,
				xAxis.z, yAxis.z, zAxis.z, 0,
				-Vector3::dotProduct(xAxis, eye), -Vector3::dotProduct(yAxis, eye), -Vector3::dotProduct(zAxis, eye), 1
			}};

			return viewMatrix;
		}

		/**
		 * @brief Create a translation matrix
		 *
		 * @param vector The translation vector
		 * @returns The translation matrix
		 */
		static Matrix4x4 translation(Vector3 vector)
		{
			Matrix4x4 translationMatrix = Matrix4x4::identity();
			translationMatrix.elements[12] = vector.x;
			translationMatrix.elements[13] = vector.y;
			translationMatrix.elements[14] = vector.z;
			return translationMatrix;
		}

		/**
		 * @brief Create a rotation matrix for the X axis
		 *
		 * @param angle The rotation angle in radians
		 * @returns The rotation matrix
		 */
		static Matrix4x4 rotationX(float angle)
		{
			Matrix4x4 rotationMatrix = Matrix4x4::identity();
			float cosAngle = cos(angle);
			float sinAngle = sin(angle);

			rotationMatrix.elements[5] = cosAngle;
			rotationMatrix.elements[6] = sinAngle;
			rotationMatrix.elements[9] = -sinAngle;
			rotationMatrix.elements[10] = cosAngle;
			return rotationMatrix;
		}

		/**
		 * @brief Create a rotation matrix for the Y axis
		 *
		 * @param angle The rotation angle in radians
		 * @returns The rotation matrix
		 */
		static Matrix4x4 rotationY(float angle)
		{
			Matrix4x4 rotationMatrix = Matrix4x4::identity();
			float cosAngle = cos(angle);
			float sinAngle = sin(angle);

			rotationMatrix.elements[0] = cosAngle;
			rotationMatrix.elements[2] = -sinAngle;
			rotationMatrix.elements[8] = sinAngle;
			rotationMatrix.elements[10] = cosAngle;
			return rotationMatrix;
		}

		/**
		 * @brief Create a rotation matrix for the Z axis
		 *
		 * @param angle The rotation angle in radians
		 * @returns The rotation matrix
		 */
		static Matrix4x4 rotationZ(float angle)
		{
			Matrix4x4 rotationMatrix = Matrix4x4::identity();
			float cosAngle = cos(angle);
			float sinAngle = sin(angle);

			rotationMatrix.elements[0] = cosAngle;
			rotationMatrix.elements[1] = sinAngle;
			rotationMatrix.elements[4] = -sinAngle;
			rotationMatrix.elements[5] = cosAngle;
			return rotationMatrix;
		}

		/**
		 * @brief Create a 4x4 identity matrix
		 *
		 * @returns The 4x4 identity matrix
		 */
		static Matrix4x4 identity() noexcept
		{
			return Matrix4x4
			{{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			}};
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