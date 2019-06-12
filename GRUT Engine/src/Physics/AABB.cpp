#include "grutpch.h"
#include "AABB.h"

namespace GRUT {
  bool AABB::Contains(const Vector3& p_point) const {
    return 
      (p_point.x >= m_min.x && p_point.x <= m_max.x) &&
      (p_point.y >= m_min.y && p_point.y <= m_max.y) &&
      (p_point.z >= m_min.z && p_point.z <= m_max.z);
  }
  bool AABB::Contains(const AABB& p_aabb) const {
    return Contains(p_aabb.m_min) && Contains(p_aabb.m_max);
  }

  bool AABB::Intersects(const AABB& p_other) const {
    return (m_min.x <= p_other.m_max.x && m_max.x >= p_other.m_min.x) &&
      (m_min.y <= p_other.m_max.y && m_max.y >= p_other.m_min.y) &&
      (m_min.z <= p_other.m_max.z && m_max.z >= p_other.m_min.z);
  }

  bool AABB::IntersectionExists(const AABB& a, const AABB& b) {
    return a.Intersects(b);
  }

  void AABB::Expand(const float amount) {
    m_size += amount * Vector3(1.0f, 1.0f, 1.0f);
    m_extents = 0.5 * m_size;
    m_min = m_center - m_extents;
    m_max = m_center + m_extents;
  }

  void AABB::Encapsulate(const Vector3& point) {
    m_min.x = min(m_min.x, point.x);
    m_min.y = min(m_min.y, point.y);
    m_min.z = min(m_min.z, point.z);
    m_max.x = max(m_max.x, point.x);
    m_max.y = max(m_max.y, point.y);
    m_max.z = max(m_max.z, point.z);
  }
  void AABB::Encapsulate(const AABB& other) {
    m_min.x = min(m_min.x, other.m_min.x);
    m_min.y = min(m_min.y, other.m_min.y);
    m_min.z = min(m_min.z, other.m_min.z);
    m_max.x = max(m_max.x, other.m_max.x);
    m_max.y = max(m_max.y, other.m_max.y);
    m_max.z = max(m_max.z, other.m_max.z);
  }
  AABB AABB::Encapsulate(const AABB& a, const AABB& b) {
    Vector3 aabbMin = Vector3 {
      min(a.m_min.x, b.m_min.x),
      min(a.m_min.y, b.m_min.y),
      min(a.m_min.z, b.m_min.z)
    };
    Vector3 aabbMax = Vector3 {
      max(a.m_max.x, b.m_max.x),
      max(a.m_max.y, b.m_max.y),
      max(a.m_max.z, b.m_max.z)
    };
    return AABBFromMinMax(aabbMin, aabbMax);
  }

  float AABB::SurfaceArea() const {
    return 2.0f * (m_size.x * m_size.y + m_size.y * m_size.z + m_size.x * m_size.z);
  }
}
