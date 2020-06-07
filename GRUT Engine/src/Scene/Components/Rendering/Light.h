#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <GRUTMath.h>
#include "../Component.h"
#include "Core/Parallelism/SpinLock.h"

namespace GRUT {
    using namespace GRUT::Math;
    enum class LightType {
        POINT,
        DIRECTIONAL,
        SPOTLIGHT
    };
    class Light : public Component {
        private:
            LightType m_type = LightType::POINT;
            SpinLock  m_spinlock;

        public:
            Vector3 direction{ 0.0f, 0.0f, 1.0f };
            Vector3 color{ 1.0f, 1.0f, 1.0f };
            void SetType(LightType p_type);
    };
}