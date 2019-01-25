#pragma once
#include <math.h>
#include <iostream>

namespace GRUT {
  namespace Math {
    template<short N>
    class Vector {
    private:
      float m_vals[N];
    public:
      Vector() : m_vals{ 0 } {};
      template <typename ...T> Vector(T... args) : m_vals{ args... } {}
      float& operator[] (short index) const {
        return const_cast<float*>(reinterpret_cast<const float*>(this))[index];
      }
      operator const float*() const {
        return m_vals;
      }

      Vector& operator+= (const Vector & other) {
        for (short i = 0; i < N; ++i) {
          (*this)[i] += other[i];
        }
        return *this;
      }
      Vector operator+ (const Vector & other) const {
        Vector result(*this);
        return result += other;
      }

      Vector& operator-= (const Vector & other) {
        for (short i = 0; i < N; ++i) {
          (*this)[i] -= other[i];
        }
        return *this;
      }
      Vector operator- (const Vector & other) const {
        Vector result(*this);
        return result -= other;
      }

      Vector& operator*= (const Vector & other) {
        for (short i = 0; i < N; ++i) {
          (*this)[i] *= other[i];
        }
        return *this;
      }
      Vector operator* (const Vector & other) const {
        Vector result(*this);
        return result *= other;
      }
      Vector& operator*= (float & scalar) {
        for (short i = 0; i < N; ++i) {
          (*this)[i] *= scalar;
        }
        return *this;
      }
      Vector operator* (float & scalar) const {
        Vector result(*this);
        return result *= scalar;
      }

      Vector& operator/= (const Vector & other) {
        for (short i = 0; i < N; ++i) {
          (*this)[i] /= other[i];
        }
        return *this;
      }
      Vector operator/ (const Vector & other) const  {
        Vector result(*this);
        return result /= other;
      }
      Vector& operator/= (float & scalar) {
        for (short i = 0; i < N; ++i) {
          (*this)[i] /= scalar;
        }
        return *this;
      }
      Vector operator/ (float & scalar) const  {
        Vector result(*this);
        return result /= scalar;
      }

      float Dot(const Vector & other) const {
        float sum = 0.0f;
        for (short i = 0; i < N; ++i) {
          sum += (*this)[i] * other[i];
        }
        return sum;
      }

      float Magnitude() const {
        float membersSquared = 0.0f;
        for (short i = 0; i < N; ++i) {
          membersSquared += (*this)[i] * (*this)[i];
        }
        return sqrt(membersSquared);
      }

      Vector& Normalize() {
        float mag = Magnitude();
        for (short i = 0; i < N; ++i) {
          (*this)[i] /= mag;
        }
        return *this;
      }
      Vector Normalized() const {
        Vector normalVector(*this);
        return normalVector.Normalize();
      }

      
      template<short M = N> typename std::enable_if< (M == 3), Vector >::type Cross(const Vector & other) const {
        return Vector({
          y() * other.z() - z() * other.y(),
          z() * other.x() - x() * other.z(),
          x() * other.y() - y() * other.x()
        });
      }

      float x() const { return m_vals[0]; }
      template<short M = N> typename std::enable_if < (M > 1), float >::type y() const { return m_vals[1]; }
      template<short M = N> typename std::enable_if < (M > 2), float >::type z() const { return m_vals[2]; }
      template<short M = N> typename std::enable_if < (M > 3), float >::type w() const { return m_vals[3]; }

      float r() const { return m_vals[0]; }
      template<short M = N> typename std::enable_if < (M > 1), float >::type g() { return m_vals[1]; }
      template<short M = N> typename std::enable_if < (M > 2), float >::type b() { return m_vals[2]; }
      template<short M = N> typename std::enable_if < (M > 3), float >::type a() { return m_vals[3]; }

      friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
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
  }
}