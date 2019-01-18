#pragma once
#include <memory>
#include "Core/Jobs/Job.h"

namespace GRUT {
  struct FrameParams {
    bool isDone = true;
    float deltaTime;
    std::weak_ptr<Job> updateJob;
    std::weak_ptr<Job> renderJob;
    std::weak_ptr<Job> memoryJob;
  };
}