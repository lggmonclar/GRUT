#pragma once

namespace GRUT {
  namespace Math {
    constexpr double PI = 3.14;

    inline double deg2rad(double deg) {
      return (deg * PI) / 180.0;
    }

    inline double rad2deg(double rad) {
      return (180.0 * rad) / PI;
    }
  }
}
