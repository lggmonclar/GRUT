#pragma once

namespace GRUT {
  namespace Math {
    constexpr double PI = 3.14;

    inline double deg2rad(const double &deg) {
      return (deg * PI) / 180.0;
    }

    inline double rad2deg(const double &rad) {
      return (180.0 * rad) / PI;
    }

    inline float min(const float &f1, const float &f2) {
      return f1 < f2 ? f1 : f2;
    }

    inline float max(const float &f1, const float &f2) {
      return f1 > f2 ? f1 : f2;
    }

    inline float abs(const float &v) {
      return v < 0 ? -v : v; 
    }

    inline int abs(const int &v) {
      return v < 0 ? -v : v; 
    }
  }
}
