#pragma once
#include <memory>
#include "Core/Jobs/Job.h"

namespace GRUT {
    struct FrameParams {
        short index = 0;
        bool isDone = true;
        float deltaTime = 0.0f;
        std::weak_ptr<Job> physicsJob;
        std::weak_ptr<Job> updateJob;
        std::weak_ptr<Job> renderJob;
        std::weak_ptr<Job> memoryJob;
    };
}