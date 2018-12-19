#pragma once
#include <math.h>
#include <initializer_list>
#include "Vector.h"

namespace GRUT {
	namespace Math {
		template<short N>
		class BaseMatrix {
		protected:
			float vals[N * N];
			BaseMatrix() : vals{} {
				for (short i = 0; i < N; ++i) {
					vals[N*i+i] = 1.0f;
				}
			}
			template <typename ...T>
			BaseMatrix(T... args) : vals{ args...} {}
			BaseMatrix(const BaseMatrix &other) {
				for (short i = 0; i < N * N; ++i) {
					vals[i] = other[i];
				}
			}
		public:
			BaseMatrix& operator+= (BaseMatrix & other) {
				for (short i = 0; i < N * N; ++i) {
					vals[i] += other.vals[i];
				}
				return *this;
			}
			template<typename T> T operator+ (const T & other) const {
				T result(*this);
				return result += other;
			}

			BaseMatrix& operator-= (BaseMatrix & other) {
				for (short i = 0; i < N * N; ++i) {
					vals[i] -= other.vals[i];
				}
				return *this;
			}
			template<typename T> T operator- (const T & other) const {
				T result(*this);
				return result -= other;
			}

			BaseMatrix& operator*= (const BaseMatrix & other) {
				BaseMatrix<N> result;
				int n = N;
				for (short i = 0; i < N; ++i) {
					for (short j = 0; j < N; ++j) {
						float sum = 0.0f;
						for (int k = 0; k < N; ++k) {
							sum += vals[i * N + k] * other.vals[k + j * N];
						}
						result.vals[i * N + j] = sum;
					}
				}
				*this = result;
				return *this;
			}
			template<typename T> T operator* (const T & other) const {
				T result(*this);
				return result *= other;
			}
			BaseMatrix& operator*= (float & scalar) {
				for (short i = 0; i < N * N; ++i) {
					vals[i] *= scalar;
				}
				return *this;
			}
			template<typename T> T operator* (float & scalar) const {
				T result(*this);
				return result *= scalar;
			}

			template<typename T> T& transpose() {
				T transposed;
				for (short i = 0; i < N; ++i) {
					for (short j = 0; j < N; ++j) {
						transposed.vals[i * N + j] = vals[i + j * N];
					}
				}
				*this = transposed;
				return *this;
			}
			template<typename T> T transposed() {
				T transposedThis = *this;
				return transposedThis.transpose();
			}

			template<typename T> T& scale(float scalar) {
				for (short i = 0; i < N; ++i) {
					vals[N*i + i] *= scalar;
				}
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& os, const BaseMatrix& mat) {
				os << "[";
				for (short i = 0; i < N; ++i) {
					os << "[";
					for (short j = 0; j < N; ++j) {
						os << mat.vals[i + j * N];
						if (j < N - 1)
							os << ", ";
					}
					os << "]";
					if (i < N - 1) {
						os << ", ";
						os << "\n";
					}
				}
				os << "]";
				return os;
			}
		};

		class Matrix2 : public BaseMatrix<2> {
		public:
			template <typename ...T>
			Matrix2(T... args) : BaseMatrix<2>(args...) {}
			Vector2& operator[] (short index) {
				return reinterpret_cast<Vector2*>(this)[index];
			}
			Vector2& operator[] (short index) const {
				return const_cast<Vector2*>(reinterpret_cast<const Vector2*>(this))[index];
			}
			using BaseMatrix<2>::operator=;
		};
		class Matrix3 : public BaseMatrix<3> {
		public:
			template <typename ...T>
			Matrix3(T... args) : BaseMatrix<3>(args...) {}
			Vector3& operator[] (short index) {
				return reinterpret_cast<Vector3*>(this)[index];
			}
			Vector3& operator[] (short index) const {
				return const_cast<Vector3*>(reinterpret_cast<const Vector3*>(this))[index];
			}
			using BaseMatrix<3>::operator=;
		};
		class Matrix4 : public BaseMatrix<4> {
		public:
			template <typename ...T>
			Matrix4(T... args) : BaseMatrix<4>(args...) {}
			Vector4& operator[] (short index) {
				return reinterpret_cast<Vector4*>(this)[index];
			}
			Vector4& operator[] (short index) const {
				return const_cast<Vector4*>(reinterpret_cast<const Vector4*>(this))[index];
			}
			using BaseMatrix<4>::operator=;

			Matrix4& scale(float scalar) {
				for (short i = 0; i < 3; ++i) {
					vals[3*i + i] *= scalar;
				}
				return *this;
			}
			Matrix4& rotateX(float ang) {
				float c = cos(ang);
				float s = sin(ang);

				*this *= Matrix4(
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, c, -s, 0.0f,
					0.0f, s, c, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				);
				return *this;
			}
			Matrix4& rotateY(float ang) {
				float c = cos(ang);
				float s = sin(ang);

				*this *= Matrix4(
					c, 0.0f, s, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					-s, 0.0f, c, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				);
				return *this;
			}
			Matrix4& rotateZ(float ang) {
				float c = cos(ang);
				float s = sin(ang);

				*this *= Matrix4(
					c, -s, 0.0f, 0.0f,
					s, c, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				);

				return *this;
			}
			Matrix4& rotateAbout(float deg, const Vector3& axis) {
				float c = cos(deg);
				float s = sin(deg);
				Vector3 ax = axis.normalized();

				*this *= Matrix4(
					ax.x * ax.x * (1 - c) + c, ax.x * ax.y * (1 - c) + ax.z * s, ax.x * ax.z * (1 - c) - ax.y * s, 0.0F,

					ax.x * ax.y * (1 - c) - ax.z * s, ax.y * ax.y * (1 - c) + c, ax.y * ax.z * (1 - c) + ax.x * s, 0.0F,

					ax.x * ax.z * (1 - c) + ax.y * s, ax.y * ax.z * (1 - c) - ax.x * s, ax.z * ax.z * (1 - c) + c, 0.0F,

					0.0F, 0.0F, 0.0F, 1.0F
				);

				return *this;
			}
			Matrix4& translate(float x, float y, float z) {
				*this *= Matrix4(
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					x	, y	  , z	, 1.0f
				);

				return *this;
			}
			static Matrix4 orthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
				float m00 = 2.0f / (right - left);
				float m11 = 2.0f / (top - bottom);
				float m22 = -2.0f / (farPlane - nearPlane);
				float m30 = -(right + left) / (right - left);
				float m31 = -(top + bottom) / (top - bottom);
				float m32 = -(farPlane + nearPlane) / (farPlane - nearPlane);

				return Matrix4(
					m00, 0.0f, 0.0f, 0.0f,
					0.0f, m11, 0.0f, 0.0f,
					0.0f, 0.0f, m22, 0.0f,
					m30, m31, m32, 1.0f
				);
			}
			static Matrix4 perspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
				float tanHalfFov = tan(fieldOfView / 2.0f);

				float m00 = 1.0f / (aspectRatio * tanHalfFov);
				float m11 = 1.0f / tanHalfFov;
				float m22 = -(farPlane + nearPlane) / (farPlane - nearPlane);
				float m23 = -1.0f;
				float m32 = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);

				return Matrix4(
					m00, 0.0f, 0.0f, 0.0f,
					0.0f, m11, 0.0f, 0.0f,
					0.0f, 0.0f, m22, m23,
					0.0f, 0.0f, m32, 0.0f
				);
			}
			Matrix4& lookAt(const Vector3 &position, const Vector3 &target, const Vector3 &worldUp) {
				Vector3 zAxis = (position - target).normalized();
				Vector3 xAxis = worldUp.cross(zAxis).normalized();
				Vector3 yAxis = zAxis.cross(xAxis);

				vals[0] = xAxis.x;
				vals[1] = yAxis.x;
				vals[2] = zAxis.x;

				vals[4] = xAxis.y;
				vals[5] = yAxis.y;
				vals[6] = zAxis.y;

				vals[8] = xAxis.z;
				vals[9] = yAxis.z;
				vals[10] = zAxis.z;

				vals[12] = -(xAxis.dot(position));
				vals[13] = -(yAxis.dot(position));
				vals[14] = -(zAxis.dot(position));

				return *this;
			}
		};
	}
}