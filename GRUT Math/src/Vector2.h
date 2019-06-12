#pragma once
#include <math.h>
#include <iostream>

namespace GRUT {
  namespace Math {
    class Vector2 {
    public:
      union {
        struct {
          float x, y;
        };
        struct {
          float r, g;
        };
        float values[2];
      };

      Vector2() : values{ 0 } {};
      Vector2(float p_x, float p_y) : x(p_x), y(p_y) {}
      
      float& operator[] (short index) const {
        return const_cast<float*>(reinterpret_cast<const float*>(this))[index];
      }
      operator const float* () const {
        return values;
      }

      Vector2& operator+= (const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
      }
      Vector2 operator+ (const Vector2& other) const {
        Vector2 result(*this);
        return result += other;
      }

      Vector2& operator-= (const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
      }
      Vector2 operator- (const Vector2& other) const {
        Vector2 result(*this);
        return result -= other;
      }      
      Vector2 operator- () const {
        Vector2 result(*this);
        return result *= -1.0f;
      }

      Vector2& operator*= (const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
      }
      Vector2 operator* (const Vector2& other) const {
        Vector2 result(*this);
        return result *= other;
      }
      Vector2& operator*= (const float& other) {
        x *= other;
        y *= other;
        return *this;
      }
      Vector2 operator* (const float& other) const {
        Vector2 result(*this);
        return result *= other;
      }
      friend Vector2 operator*(const float& scalar, const Vector2& v) {
        return v * scalar;
      }

      Vector2& operator/= (const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
      }
      Vector2 operator/ (const Vector2& other) const {
        Vector2 result(*this);
        return result /= other;
      }
      Vector2& operator/= (const float& other) {
        x /= other;
        y /= other;
        return *this;
      }
      Vector2 operator/ (const float& other) const {
        Vector2 result(*this);
        return result /= other;
      }
      friend Vector2 operator/(const float& scalar, const Vector2& v) {
        return v / scalar;
      }

      float Dot(const Vector2& other) const {
        return x * other.x + y * other.y;
      }

      float Magnitude() {
        return sqrt(x * x + y * y);
      }

      Vector2 &Normalize() {
        float mag = Magnitude();
        x /= mag;
        y /= mag;
        return *this;
      }
      Vector2 Normalized() const {
        Vector2 normal(*this);
        return normal.Normalized();
      }

      friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "[" << vec.x << ", " << vec.y << "]";
        return os;
      }
    };
  }
}