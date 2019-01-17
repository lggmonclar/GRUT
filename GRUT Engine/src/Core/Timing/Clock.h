#pragma once
#include <chrono>
#include "Core/GRUTAlias.h"
#include "DLLMacros.h"

namespace GRUT {
  class Clock {
    using Nanoseconds = std::chrono::nanoseconds;
    using HighResClock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<HighResClock>;

    TimePoint m_startTime;
    TimePoint m_currentTime;
    double m_deltaTime;
    double m_elapsedTime;
    double m_elapsedUnscaledTime;
    U64 m_timeFrame;

  public:
    float timeScale;
    bool isPaused;

    Clock();

    Clock& operator=(const Clock& inClock) = delete;
    Clock& operator=(Clock&& inClock) = delete;

    void UpdateTime();
    double GetDeltaTime() const;
    double GetElapsedTime() const;
    double GetElapsedUnscaledTime() const;

    U64 GetTimeFrame() const;

    static U64 GetTimestamp();
  };
}
