#pragma once
#include <math.h>
#include <initializer_list>
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
        tOther.transpose();
        for (short i = 0; i < N; ++i) {
          for (short j = 0; j < N; ++j) {
            auto row = (*this)[i];
            auto col = tOther[j];
            result[i][j] = row.dot(col);
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

      Matrix& transpose() {
        Matrix transposed;
        for (short i = 0; i < N; ++i) {
          for (short j = 0; j < N; ++j) {
            transposed.m_vals[i * N + j] = m_vals[i + j * N];
          }
        }
        *this = transposed;
        return *this;
      }
      Matrix transposed() const {
        Matrix transposedThis(*this);
        return transposedThis.transpose();
      }

      Matrix& scale(float scalar) {
        for (short i = 0; i < N - 1; ++i) {
          m_vals[N*i + i] *= scalar;
        }
        return *this;
      }
      template<short M = N> typename std::enable_if< (M == 3), Matrix & >::type scale(float scalar) {
        for (short i = 0; i < 3; ++i) {
          m_vals[N*i + i] *= scalar;
        }
        return *this;
      }

      template<short M = N> typename std::enable_if< (M > 2), Matrix & >::type rotateX(float ang) {
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
      template<short M = N> typename std::enable_if< (M > 2), Matrix & >::type rotateY(float ang) {
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
      Matrix & rotateZ(float ang) {
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

      template<short M = N> typename std::enable_if< (M > 2), Matrix & >::type rotateAbout(float deg, const Vector<3>& axis) {
        float c = cos(deg);
        float s = sin(deg);
        Vector<3> v = axis.normalized();

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
      Matrix& translate(const Vector<N> & v) {
        (*this)[N - 1] = v;
        return *this;
      };

      template<short M = N> typename static std::enable_if< (M > 3), Matrix & >::type orthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        Matrix mat;
        mat[0][0] = 2.0f / (right - left);
        mat[1][1] = 2.0f / (top - bottom);
        mat[2][2] = -2.0f / (farPlane - nearPlane);
        mat[3][0] = -(right + left) / (right - left);
        mat[3][1] = -(top + bottom) / (top - bottom);
        mat[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

        return mat;
      }
      template<short M = N> typename static std::enable_if< (M > 3), Matrix & >::type perspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
        Matrix mat;
        float tanHalfFov = tan(fieldOfView / 2.0f);

        mat[0][0] = 1.0f / (aspectRatio * tanHalfFov);
        mat[1][1] = 1.0f / tanHalfFov;
        mat[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
        mat[2][3] = -1.0f;
        mat[3][2] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);

        return mat;
      }
      template<short M = N> typename std::enable_if< (M > 3), Matrix & >::type lookAt(const Vector<3> &position, const Vector<3> &target, const Vector<3> &worldUp) {
        Vector<3> zAxis = (position - target).normalized();
        Vector<3> xAxis = worldUp.cross(zAxis).normalized();
        Vector<3> yAxis = zAxis.cross(xAxis);

        (*this)[0][0] = xAxis.x;
        (*this)[0][1] = yAxis.x;
        (*this)[0][2] = zAxis.x;

        (*this)[1][0] = xAxis.y;
        (*this)[1][1] = yAxis.y;
        (*this)[1][2] = zAxis.y;

        (*this)[2][0] = xAxis.z;
        (*this)[2][1] = yAxis.z;
        (*this)[2][2] = zAxis.z;

        (*this)[3][0] = -(xAxis.dot(position));
        (*this)[3][1] = -(yAxis.dot(position));
        (*this)[3][2] = -(zAxis.dot(position));

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