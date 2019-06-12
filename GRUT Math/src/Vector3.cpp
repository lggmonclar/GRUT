#include "Vector3.h"
#include "Vector4.h"

namespace GRUT {
  namespace Math {
    Vector3 Vector3::ApplyMatrix4(const Matrix4& matrix) const {
      Vector4 v(x, y, z, 1.0f);
      v *= matrix;

      return Vector3(v.x, v.y, v.z);
    }
  }
}
