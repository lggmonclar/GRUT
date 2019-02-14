#pragma once
#include <math.h>
#include "Vector.h"

namespace GRUT {
  namespace Math {
    template<short N>
    class Matrix {
    private:
      float m_vals[N * N];
    public:
      Matrix() : m_vals{} {
        for (short i = 0; i < N; ++i) {
          m_vals[N*i + i] = 1.0f;
        }
      }
      template <typename ...T>
      Matrix(T... args) : m_vals{ args... } {}

      operator const float*() const {
        return m_vals;
      }

      Vector<N>& operator[] (short index) const {
        return const_cast<Vector<N>*>(reinterpret_cast<const Vector<N>*>(this))[index];
      }

      Matrix& operator+= (const Matrix & other) {
        for (short i = 0; i < N * N; ++i) {
          m_vals[i] += other.m_vals[i];
        }
        return *this;
      }
      Matrix operator+ (const Matrix & other) const {
        Matrix result(*this);
        return result += other;
      }

      Matrix& operator-= (const Matrix & other) {
        for (short i = 0; i < N * N; ++i) {
          m_vals[i] -= other.m_vals[i];
        }
        return *this;
      }
      Matrix operator- (const Matrix & other) const {
        Matrix result(*this);
        return result -= other;
      }

      Matrix& operator*= (const Matrix & other) {
        Matrix<N> result;
        Matrix<N> tOther(other);
        tOther.Transpose();
        for (short i = 0; i < N; ++i) {
          for (short j = 0; j < N; ++j) {
            auto row = (*this)[i];
            auto col = tOther[j];
            result[i][j] = row.Dot(col);
          }
        }
        *this = result;
        return *this;
      }
      Matrix operator* (const Matrix & other) const {
        Matrix result(*this);
        return result *= other;
      }
      Matrix& operator*= (const float & scalar) {
        for (short i = 0; i < N * N; ++i) {
          (*this)[i] *= scalar;
        }
        return *this;
      }
      Matrix operator* (const float & scalar) const {
        Matrix result(*this);
        return result *= scalar;
      }

      Matrix& Transpose() {
        Matrix transposed;
        for (short i = 0; i < N; ++i) {
          for (short j = 0; j < N; ++j) {
            transposed.m_vals[i * N + j] = m_vals[i + j * N];
          }
        }
        *this = transposed;
        return *this;
      }
      Matrix Transposed() const {
        Matrix transposedThis(*this);
        return transposedThis.Transpose();
      }

      template<short M = N> typename std::enable_if< (M != 3), Matrix & >::type Scale(float scalar) {
        for (short i = 0; i < N - 1; ++i) {
          m_vals[N*i + i] *= scalar;
        }
        return *this;
      }
      template<short M = N> typename std::enable_if< (M == 3), Matrix & >::type Scale(float scalar) {
        for (short i = 0; i < 3; ++i) {
          m_vals[N*i + i] *= scalar;
        }
        return *this;
      }      
      template<short M = N> typename std::enable_if< (M != 3), Matrix & >::type Scale(Vector<N - 1> vec) {
        for (short i = 0; i < N - 1; ++i) {
          m_vals[N*i + i] *= vec[i];
        }
        return *this;
      }
      template<short M = N> typename std::enable_if< (M == 3), Matrix & >::type Scale(Vector<N> vec) {
        for (short i = 0; i < 3; ++i) {
          m_vals[N*i + i] *= vec[i];
        }
        return *this;
      }

      template<short M = N> typename std::enable_if< (M > 2), Matrix & >::type RotateX(float ang) {
        float c = cos(ang);
        float s = sin(ang);
        Matrix mat;
        mat[1][1] = c;
        mat[1][2] = -s;
        mat[2][1] = s;
        mat[2][2] = c;

        *this *= mat;
        return *this;
      }
      template<short M = N> typename std::enable_if< (M > 2), Matrix & >::type RotateY(float ang) {
        float c = cos(ang);
        float s = sin(ang);
        Matrix mat;
        mat[0][0] = c;
        mat[0][2] = s;
        mat[2][0] = -s;
        mat[2][2] = c;

        *this *= mat;
        return *this;
      }
      Matrix & RotateZ(float ang) {
        float c = cos(ang);
        float s = sin(ang);
        Matrix mat;
        mat[0][0] = c;
        mat[0][1] = -s;
        mat[1][0] = s;
        mat[1][1] = c;

        *this *= mat;
        return *this;
      }

      template<short M = N> typename std::enable_if< (M > 2), Matrix & >::type RotateAbout(const Vector<3>& axis, float deg) {
        float c = cos(deg);
        float s = sin(deg);
        Vector<3> v = axis.Normalized();

        Matrix mat;
        mat[0][0] = v.x() * v.x() * (1 - c) + c;
        mat[0][1] = v.x() * v.y() * (1 - c) + v.z() * s;
        mat[0][2] = v.x() * v.z() * (1 - c) - v.y() * s;
        mat[1][0] = v.x() * v.y() * (1 - c) - v.z() * s;
        mat[1][1] = v.y() * v.y() * (1 - c) + c;
        mat[1][2] = v.y() * v.z() * (1 - c) + v.x() * s;
        mat[2][0] = v.x() * v.z() * (1 - c) + v.y() * s;
        mat[2][1] = v.y() * v.z() * (1 - c) - v.x() * s;
        mat[2][2] = v.z() * v.z() * (1 - c) + c;

        *this *= mat;
        return *this;
      }
      Matrix& Translate(const Vector<N - 1> & v) {
        Vector<N> translationVector;
        for (int i = 0; i < N - 1; i++) {
          translationVector[i] = v[i];
        }
        (*this)[N - 1] += translationVector;
        return *this;
      };

      static Matrix OrthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        Matrix mat;
        mat[0][0] = 2.0f / (right - left);
        mat[1][1] = 2.0f / (top - bottom);
        mat[2][2] = -2.0f / (farPlane - nearPlane);
        mat[3][0] = -(right + left) / (right - left);
        mat[3][1] = -(top + bottom) / (top - bottom);
        mat[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

        return mat;
      }
      static Matrix PerspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
        Matrix mat;
        float tanHalfFov = tan(fieldOfView / 2.0f);

        mat[0][0] = 1.0f / (aspectRatio * tanHalfFov);
        mat[1][1] = 1.0f / tanHalfFov;
        mat[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
        mat[2][3] = -1.0f;
        mat[3][2] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);

        return mat;
      }
      template<short M = N> typename std::enable_if< (M > 3), Matrix & >::type LookAt(const Vector<3> &position, const Vector<3> &target, const Vector<3> &worldUp) {
        Vector<3> zAxis = (position - target).Normalized();
        Vector<3> xAxis = worldUp.Cross(zAxis).Normalized();
        Vector<3> yAxis = zAxis.Cross(xAxis);

        (*this)[0][0] = xAxis.x();
        (*this)[0][1] = yAxis.x();
        (*this)[0][2] = zAxis.x();

        (*this)[1][0] = xAxis.y();
        (*this)[1][1] = yAxis.y();
        (*this)[1][2] = zAxis.y();

        (*this)[2][0] = xAxis.z();
        (*this)[2][1] = yAxis.z();
        (*this)[2][2] = zAxis.z();

        (*this)[3][0] = -(xAxis.Dot(position));
        (*this)[3][1] = -(yAxis.Dot(position));
        (*this)[3][2] = -(zAxis.Dot(position));

        return *this;
      }

      friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        os << "[";
        for (short i = 0; i < N; ++i) {
          os << mat[i];
          if (i < N - 1)
            os << ", \n";
        }
        os << "]";
        return os;
      }
    };
  }
}
