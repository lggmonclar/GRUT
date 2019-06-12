#pragma once
#include <math.h>
#include <iostream>

namespace GRUT {
  namespace Math {
    class Vector3 {
    public:
      union {
        struct {
          float x, y, z;
        };
        struct {
          float r, g, b;
        };
        float values[3];
      };

      Vector3() : values{ 0 } {};
      Vector3(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {}

      float& operator[] (short index) const {
        return const_cast<float*>(reinterpret_cast<const float*>(this))[index];
      }
      operator const float* () const {
        return values;
      }

      Vector3& operator+= (const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
      }
      Vector3 operator+ (const Vector3& other) const {
        Vector3 result(*this);
        return result += other;
      }

      Vector3& operator-= (const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
      }
      Vector3 operator- (const Vector3& other) const {
        Vector3 result(*this);
        return result -= other;
      }
      Vector3 operator- () const {
        Vector3 result(*this);
        return result *= -1.0f;
      }

      Vector3& operator*= (const Vector3& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
      }
      Vector3 operator* (const Vector3& other) const {
        Vector3 result(*this);
        return result *= other;
      }
      Vector3& operator*= (const float& other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
      }
      Vector3 operator* (const float& other) const {
        Vector3 result(*this);
        return result *= other;
      }
      friend Vector3 operator*(const float& scalar, const Vector3& v) {
        return v * scalar;
      }

      Vector3& operator/= (const Vector3& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
      }
      Vector3 operator/ (const Vector3& other) const {
        Vector3 result(*this);
        return result /= other;
      }
      Vector3& operator/= (const float& other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
      }
      Vector3 operator/ (const float& other) const {
        Vector3 result(*this);
        return result /= other;
      }
      friend Vector3 operator/(const float& scalar, const Vector3& v) {
        return v / scalar;
      }

      float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
      }

      float Magnitude() {
        return sqrt(x * x + y * y + z * z);
      }

      Vector3 Cross(const Vector3& other) const {
        auto cross = Vector3(
          y * other.z - z * other.y,
          z * other.x - x * other.z,
          x * other.y - y * other.x
        );
        return cross;
      }

      Vector3& Normalize() {
        float mag = Magnitude();
        x /= mag;
        y /= mag;
        z /= mag;
        return *this;
      }
      Vector3 Normalized() const {
        Vector3 normal(*this);
        return normal.Normalize();
      }

      Vector3 ApplyMatrix4(const class Matrix4& matrix) const;

      friend std::ostream& operator<<(std::ostream & os, const Vector3 & vec) {
        os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
        return os;
      }
    };
  }
}