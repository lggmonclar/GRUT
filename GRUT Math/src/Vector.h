#pragma once
#include <math.h>
#include <initializer_list>
#include <iostream>

namespace GRUT {
	namespace Math {
		template<short N>
		class BaseVector {
		protected:
			BaseVector() = default;
			BaseVector(const BaseVector &other) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] = other[i];
				}
			};
		public:
			float& operator[] (short index) {
				return (reinterpret_cast<float*>(this))[index];
			}
			float& operator[] (short index) const {
				return const_cast<float*>(reinterpret_cast<const float*>(this))[index];
			}

			BaseVector& operator+= (const BaseVector & other) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] += other[i];
				}
				return *this;
			}
			template<typename T> T operator+ (const T & other) const {
				T result(*this);
				return result += other;
			}

			BaseVector& operator-= (const BaseVector & other) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] -= other[i];
				}
				return *this;
			}
			template<typename T> T operator- (const T & other) const {
				T result(*this);
				return result -= other;
			}

			BaseVector& operator*= (const BaseVector & other) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] *= other[i];
				}
				return *this;
			}
			template<typename T> T operator* (const T & other) const {
				T result(*this);
				return result *= other;
			}
			BaseVector& operator*= (float & scalar) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] *= scalar;
				}
				return *this;
			}
			template<typename T> T operator* (float & scalar) const {
				T result(*this);
				return result *= scalar;
			}

			BaseVector& operator/= (const BaseVector & other) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] /= other[i];
				}
				return *this;
			}
			template<typename T> T operator/ (const T & other) const  {
				T result(*this);
				return result /= other;
			}
			BaseVector& operator/= (float & scalar) {
				for (short i = 0; i < N; ++i) {
					(*this)[i] /= scalar;
				}
				return *this;
			}
			template<typename T> T operator/ (float & scalar) const  {
				T result(*this);
				return result /= scalar;
			}

			float dot(BaseVector & other) const {
				float sum = 0.0f;
				for (short i = 0; i < N; ++i) {
					sum += (*this)[i] * other[i];
				}
				return sum;
			}
			float dot(const BaseVector & other) const {
				float sum = 0.0f;
				for (short i = 0; i < N; ++i) {
					sum += (*this)[i] * other[i];
				}
				return sum;
			}

			float magnitude() const {
				float membersSquared = 0.0f;
				for (short i = 0; i < N; ++i) {
					membersSquared += (*this)[i] * (*this)[i];
				}
				return sqrt(membersSquared);
			}

			BaseVector& normalize() {
				float mag = magnitude();
				for (short i = 0; i < N; ++i) {
					(*this)[i] /= mag;
				}
				return *this;
			}
			BaseVector normalized() const {
				BaseVector normalVector(*this);
				return normalVector.normalize();
			}

			friend std::ostream& operator<<(std::ostream& os, const BaseVector& vec) {
				os << "[";
				for (short i = 0; i < N; ++i) {
					os << vec[i];
					if (i < N - 1)
						os << ", ";
				}
				os << "]";
				return os;
			}
		};

		class Vector2 : public BaseVector<2>{
		public:
			union {
				float vals[2];
				struct {
					float x, y;
				};
				struct {
					float r, g;
				};
			};
			Vector2() : vals{} {}
			Vector2(const BaseVector<2> &copy) : BaseVector<2>(copy) {}
			Vector2(float x, float y) : vals{ x,y } {}
			using BaseVector<2>::operator=;
		};
		class Vector3 : public BaseVector<3> {
		public:
			union {
				float vals[3];
				struct {
					float x, y, z;
				};
				struct {
					float r, g, b;
				};
			};
			Vector3() : vals{} {}
			Vector3(const BaseVector<3> &copy) : BaseVector<3>(copy) {}
			Vector3(float x, float y, float z) : vals{ x,y,z } {}
			using BaseVector<3>::operator=;

			Vector3 cross(Vector3 & other) {
				return Vector3({
					y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x
				});
			}
			Vector3 cross(const Vector3 & other) const {
				return Vector3({
					y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x
				});
			}
		};
		class Vector4 : public BaseVector<4> {
		public:
			union {
				float vals[4];
				struct {
					float x, y, z, w;
				};
				struct {
					float r, g, b, a;
				};
			};
			Vector4() : vals{} {}
			Vector4(const BaseVector<4> &copy) : BaseVector<4>(copy) {}
			Vector4(float x, float y, float z, float w) : vals{ x,y,z,w } {}
			using BaseVector<4>::operator=;
		};
	}
}