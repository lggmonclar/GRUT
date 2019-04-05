#pragma once
#include <GRUTMath.h>

using namespace GRUT::Math;

namespace GRUT {
  class AABB {
  private:
    Vector<3> m_min;
    Vector<3> m_max;
    Vector<3> m_center;
    Vector<3> m_size;
    Vector<3> m_extents;

    static AABB AABBFromMinMax(const Vector<3>& min, const Vector<3>& max) {
      Vector<3> center = 0.5f * (max + min);
      Vector<3> size = 2.0f * (max - center);
      return AABB(center, size);
    }
  public:
    AABB(const Vector<3>& p_center, const Vector<3>& p_size) : m_center(p_center), m_size(p_size) {
      m_extents = 0.5f * p_size;
      m_min = m_center - m_extents;
      m_max = m_center + m_extents;
    }

    inline Vector<3> GetCenter() const { return m_center; }
    inline Vector<3> GetSize() const { return m_size; }
    inline Vector<3> GetExtents() const { return m_extents; }
    inline Vector<3> GetMin() const { return m_min; }
    inline Vector<3> GetMax() const { return m_max; }

    bool Contains(const Vector<3>& point) const;
    bool Contains(const AABB& aabb) const;

    bool Intersects(const AABB& other) const;
    static bool IntersectionExists(const AABB& a, const AABB& b);

    void Expand(const float amount);

    void Encapsulate(const Vector<3>& point);
    void Encapsulate(const AABB& other);
    static AABB Encapsulate(const AABB& a, const AABB& b);

    float SurfaceArea() const;
  };
}