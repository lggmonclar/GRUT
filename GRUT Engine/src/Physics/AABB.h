#pragma once
#include <GRUTMath.h>

using namespace GRUT::Math;

namespace GRUT {
    class AABB {
        private:
            Vector3 m_min;
            Vector3 m_max;
            Vector3 m_center;
            Vector3 m_size;
            Vector3 m_extents;

            static AABB AABBFromMinMax(const Vector3& min, const Vector3& max) {
                Vector3 center = 0.5f * (max + min);
                Vector3 size = 2.0f * (max - center);
                return AABB(center, size);
            }

        public:
            AABB(const Vector3& p_center, const Vector3& p_size) : m_center(p_center), m_size(p_size) {
                m_extents = 0.5f * p_size;
                m_min = m_center - m_extents;
                m_max = m_center + m_extents;
            }

            inline Vector3 GetCenter() const { return m_center; }
            inline Vector3 GetSize() const { return m_size; }
            inline Vector3 GetExtents() const { return m_extents; }
            inline Vector3 GetMin() const { return m_min; }
            inline Vector3 GetMax() const { return m_max; }

            bool Contains(const Vector3& point) const;
            bool Contains(const AABB& aabb) const;

            bool Intersects(const AABB& other) const;
            static bool IntersectionExists(const AABB& a, const AABB& b);

            void Expand(const float amount);

            void Encapsulate(const Vector3& point);
            void Encapsulate(const AABB& other);
            static AABB Encapsulate(const AABB& a, const AABB& b);

            float SurfaceArea() const;
    };
}