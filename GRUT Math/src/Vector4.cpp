#include "Vector4.h"
#include "Matrix4.h"

namespace GRUT {
  namespace Math {
    Vector4& Vector4::operator*=(const Matrix4& other) {
      Matrix4 tOther(other);
      tOther.Transpose();
      for (short i = 0; i < 4; ++i) {
        auto x = tOther.values[i * 4];
        auto y = tOther.values[i * 4 + 1];
        auto z = tOther.values[i * 4 + 2];
        auto w = tOther.values[i * 4 + 3];
        Vector4 v4(x, y, z, w);

        values[i] = (*this).Dot(v4);
      }
      return *this;
    }
    Vector4 Vector4::operator*(const Matrix4& other) const {
      Vector4 result(*this);
      return result *= other;
    }
  }
}
