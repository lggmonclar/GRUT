#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace GRUT {
  namespace Math {
    class Matrix4 {
    public:
      union {
        struct {
          float values[16];
        };
        struct {
          float m[4][4];
        };
        struct {
          float
            m00, m01, m02, m03,
            m10, m11, m12, m13,
            m20, m21, m22, m23,
            m30, m31, m32, m33;
        };
      };

      Matrix4() :
        values{
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1
      } {
      }

      Matrix4(float v00, float v01, float v02, float v03,
        float v10, float v11, float v12, float v13,
        float v20, float v21, float v22, float v23,
        float v30, float v31, float v32, float v33) :
        values{
          v00, v01, v02, v03,
          v10, v11, v12, v13,
          v20, v21, v22, v23,
          v30, v31, v32, v33
      } {
      }

      Matrix4(const Vector4& i, const Vector4& j, const Vector4& k, const Vector4& l) :
        values{
          i.x, i.y, i.z, i.w,
          j.x, j.y, j.z, j.w,
          k.x, k.y, k.z, k.w,
          l.x, l.y, l.z, l.w,
      } {
      }

      Vector4& operator[] (short index) const {
        return const_cast<Vector4*>(reinterpret_cast<const Vector4*>(this))[index];
      }

      operator const float* () const {
        return values;
      }

      Matrix4 operator *(const Matrix4& N) const {
        Matrix4 M = *this;
        return M *= N;
      }

      Matrix4& operator *= (const Matrix4& N) {
        m00 = m00 * N.m00 + m01 * N.m10 + m02 * N.m20 + m03 * N.m30;
        m01 = m00 * N.m01 + m01 * N.m11 + m02 * N.m21 + m03 * N.m31;
        m02 = m00 * N.m02 + m01 * N.m12 + m02 * N.m22 + m03 * N.m32;
        m03 = m00 * N.m03 + m01 * N.m13 + m02 * N.m23 + m03 * N.m33;

        m10 = m10 * N.m00 + m11 * N.m10 + m12 * N.m20 + m13 * N.m30;
        m11 = m10 * N.m01 + m11 * N.m11 + m12 * N.m21 + m13 * N.m31;
        m12 = m10 * N.m02 + m11 * N.m12 + m12 * N.m22 + m13 * N.m32;
        m13 = m10 * N.m03 + m11 * N.m13 + m12 * N.m23 + m13 * N.m33;

        m20 = m20 * N.m00 + m21 * N.m10 + m22 * N.m20 + m23 * N.m30;
        m21 = m20 * N.m01 + m21 * N.m11 + m22 * N.m21 + m23 * N.m31;
        m22 = m20 * N.m02 + m21 * N.m12 + m22 * N.m22 + m23 * N.m32;
        m23 = m20 * N.m03 + m21 * N.m13 + m22 * N.m23 + m23 * N.m33;

        m30 = m30 * N.m00 + m31 * N.m10 + m32 * N.m20 + m33 * N.m30;
        m31 = m30 * N.m01 + m31 * N.m11 + m32 * N.m21 + m33 * N.m31;
        m32 = m30 * N.m02 + m31 * N.m12 + m32 * N.m22 + m33 * N.m32;
        m33 = m30 * N.m03 + m31 * N.m13 + m32 * N.m23 + m33 * N.m33;

        return *this;
      }
      Matrix4& operator*= (const float& scalar) {
        for (short i = 0; i < 16; ++i) {
          values[i] *= scalar;
        }
        return *this;
      }
      Matrix4 operator* (const float& scalar) const {
        Matrix4 result(*this);
        return result *= scalar;
      }

      Matrix4& operator+= (const Matrix4& other) {
        for (short i = 0; i < 16; ++i) {
          values[i] += other.values[i];
        }
        return *this;
      }
      Matrix4 operator+ (const Matrix4& other) const {
        Matrix4 result(*this);
        return result += other;
      }

      Matrix4& operator-= (const Matrix4& other) {
        for (short i = 0; i < 16; ++i) {
          values[i] -= other.values[i];
        }
        return *this;
      }
      Matrix4 operator- (const Matrix4& other) const {
        Matrix4 result(*this);
        return result -= other;
      }

      Matrix4& Transpose() {
        Matrix4 transposed;
        for (short i = 0; i < 4; ++i) {
          for (short j = 0; j < 4; ++j) {
            transposed.values[i * 4 + j] = values[i + j * 4];
          }
        }
        *this = transposed;
        return *this;
      }
      Matrix4 Transposed() const {
        Matrix4 transposedThis(*this);
        return transposedThis.Transpose();
      }

      Matrix4& Scale(float scalar) {
        m00 *= scalar;
        m11 *= scalar;
        m22 *= scalar;
        return *this;
      }

      Matrix4& Scale(Vector3 vec) {
        m00 *= vec.x;
        m11 *= vec.y;
        m22 *= vec.z;
        return *this;
      }

      Matrix4& Scale(Vector4 vec) {
        m00 *= vec.x;
        m11 *= vec.y;
        m22 *= vec.z;
        m33 *= vec.w;
        return *this;
      }

      Matrix4& RotateX(float ang) {
        float c = cos(ang);
        float s = sin(ang);
        Matrix4 mat;
        mat.m11 = c;
        mat.m12 = -s;
        mat.m21 = s;
        mat.m22 = c;

        *this *= mat;
        return *this;
      }

      Matrix4& RotateY(float ang) {
        float c = cos(ang);
        float s = sin(ang);
        Matrix4 mat;
        mat.m00 = c;
        mat.m02 = s;
        mat.m20 = -s;
        mat.m22 = c;

        *this *= mat;
        return *this;
      }

      Matrix4& RotateZ(float ang) {
        float c = cos(ang);
        float s = sin(ang);
        Matrix4 mat;
        mat.m00 = c;
        mat.m01 = -s;
        mat.m10 = s;
        mat.m11 = c;

        *this *= mat;
        return *this;
      }

      Vector3 GetRotation() {
        float x, y, z;

        float sp = -m21;
        if (sp <= -1.0f) {
          x = -1.560796f; //-pi/2
        }
        else if (sp >= 1.0f) {
          x = 1.570796f;
        }
        else {
          x = asin(sp);
        }

        //Check for Gimbal lock case, giving a slight tolerance for numerical imprecision
        if (fabs(sp) > 0.9999f) {

          //We are looking straight up or down.
          //Slam Z to zero and just set Y
          z = 0.0f;
          y = atan2(-m02, m00);
        }
        else {
          //Compute Y from m13 and m33
          y = atan2(m20, m22);

          //Compute Z from m21 and m22
          z = atan2(m01, m11);
        }

        return Vector3(x, y, z);
      }

      Matrix4& SetRotation(const Vector3& p_rotation) {
        auto x = p_rotation.x;
        auto y = p_rotation.y;
        auto z = p_rotation.z;
        m00 = cos(y) * cos(z) - sin(y) * sin(x) * sin(z);
        m01 = -sin(z) * cos(x);
        m02 = sin(y) * cos(z) + cos(y) * sin(x) * sin(z);

        m10 = cos(y) * sin(z) + sin(y) * sin(x) * cos(z);
        m11 = cos(z) * cos(x);
        m12 = sin(z) * sin(y) - cos(y) * sin(x) * cos(z);

        m20 = -sin(y) * cos(x);
        m21 = sin(x);
        m22 = cos(y) * cos(x);

        return *this;
      }

      Matrix4& SetPosition(const Vector3& p_pos) {
        m30 = p_pos.x;
        m31 = p_pos.y;
        m32 = p_pos.z;

        return *this;
      }

      Matrix4& RotateAbout(const Vector3& axis, float deg) {
        float c = cos(deg);
        float s = sin(deg);
        Vector3 v = axis.Normalized();

        Matrix4 mat;
        mat.m00 = v.x * v.x * (1 - c) + c;
        mat.m01 = v.x * v.y * (1 - c) + v.z * s;
        mat.m02 = v.x * v.z * (1 - c) - v.y * s;
        mat.m10 = v.x * v.y * (1 - c) - v.z * s;
        mat.m11 = v.y * v.y * (1 - c) + c;
        mat.m12 = v.y * v.z * (1 - c) + v.x * s;
        mat.m20 = v.x * v.z * (1 - c) + v.y * s;
        mat.m21 = v.y * v.z * (1 - c) - v.x * s;
        mat.m22 = v.z * v.z * (1 - c) + c;

        *this *= mat;
        return *this;
      }
      Matrix4 & Translate(const Vector3 & v) {
        m30 += v.x;
        m31 += v.y;
        m32 += v.z;
        return *this;
      };

      static Matrix4 OrthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
        Matrix4 mat;
        mat.m00 = 2.0f / (right - left);
        mat.m11 = 2.0f / (top - bottom);
        mat.m22 = -2.0f / (farPlane - nearPlane);
        mat.m30 = -(right + left) / (right - left);
        mat.m31 = -(top + bottom) / (top - bottom);
        mat.m32 = -(farPlane + nearPlane) / (farPlane - nearPlane);

        return mat;
      }
      static Matrix4 PerspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
        Matrix4 mat;
        float tanHalfFov = tan(fieldOfView / 2.0f);

        mat.m00 = 1.0f / (aspectRatio * tanHalfFov);
        mat.m11 = 1.0f / tanHalfFov;
        mat.m22 = -(farPlane + nearPlane) / (farPlane - nearPlane);
        mat.m23 = -1.0f;
        mat.m32 = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);

        return mat;
      }
      static Matrix4 LookAt(const Vector3 & position, const Vector3 & target, const Vector3 & worldUp) {
        Matrix4 mat;
        Vector3 zAxis = (position - target).Normalized();
        Vector3 xAxis = worldUp.Cross(zAxis).Normalized();
        Vector3 yAxis = zAxis.Cross(xAxis);

        mat.m00 = xAxis.x;
        mat.m01 = yAxis.x;
        mat.m02 = zAxis.x;

        mat.m10 = xAxis.y;
        mat.m11 = yAxis.y;
        mat.m12 = zAxis.y;

        mat.m20 = xAxis.z;
        mat.m21 = yAxis.z;
        mat.m22 = zAxis.z;

        mat.m30 = -(xAxis.Dot(position));
        mat.m31 = -(yAxis.Dot(position));
        mat.m32 = -(zAxis.Dot(position));

        return mat;
      }
    };
  }
}