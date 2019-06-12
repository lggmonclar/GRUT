#pragma once
#include <math.h>
#include <iostream>

namespace GRUT {
  namespace Math {
    class Vector4 {
    public:
      union {
        struct {
          float x, y, z, w;
        };
        struct {
          float r, g, b, a;
        };
        float values[4];
      };

      Vector4() : values{ 0 } {};
      Vector4(float p_x, float p_y, float p_z, float p_w) : x(p_x), y(p_y), z(p_z), w(p_w) {}

      float& operator[] (short index) const {
        return const_cast<float*>(reinterpret_cast<const float*>(this))[index];
      }
      operator const float* () const {
        return values;
      }

      Vector4& operator+= (const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
      }
      Vector4 operator+ (const Vector4& other) const {
        Vector4 result(*this);
        return result += other;
      }

      Vector4& operator-= (const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
      }
      Vector4 operator- (const Vector4& other) const {
        Vector4 result(*this);
        return result -= other;
      }
      Vector4 operator- () const {
        Vector4 result(*this);
        return result *= -1.0f;
      }

      Vector4& operator*= (const Vector4& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
      }
      Vector4 operator* (const Vector4& other) const {
        Vector4 result(*this);
        return result *= other;
      }
      Vector4& operator*= (const float& other) {
        x *= other;
        y *= other;
        z *= other;
        w *= other;
        return *this;
      }
      Vector4 operator* (const float& other) const {
        Vector4 result(*this);
        return result *= other;
      }
      Vector4& operator*= (const class Matrix4& other);
      Vector4 operator* (const class Matrix4& other) const;

      friend Vector4 operator*(const float& scalar, const Vector4& v) {
        return v * scalar;
      }

      Vector4& operator/= (const Vector4& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
      }
      Vector4 operator/ (const Vector4& other) const {
        Vector4 result(*this);
        return result /= other;
      }
      Vector4& operator/= (const float& other) {
        x /= other;
        y /= other;
        z /= other;
        w /= other;
        return *this;
      }
      Vector4 operator/ (const float& other) const {
        Vector4 result(*this);
        return result /= other;
      }
      friend Vector4 operator/(const float& scalar, const Vector4& v) {
        return v / scalar;
      }

      float Dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
      }

      float Magnitude() {
        return sqrt(x * x + y * y + z * z + w * w);
      }

      Vector4& Normalize() {
        float mag = Magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
        return *this;
      }
      Vector4 Normalized() const {
        Vector4 normal(*this);
        return normal.Normalized();
      }

      friend std::ostream& operator<<(std::ostream & os, const Vector4 & vec) {
        os << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
        return os;
      }
    };
  }
}