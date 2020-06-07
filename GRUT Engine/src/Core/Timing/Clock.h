#pragma once
#include <chrono>
#include "Core/GRUTAlias.h"
#include "DLLMacros.h"

namespace GRUT {
    class Clock {
        private:
            using Nanoseconds = std::chrono::nanoseconds;
            using HighResClock = std::chrono::high_resolution_clock;
            using TimePoint = std::chrono::time_point<HighResClock>;

            TimePoint m_startTime;
            TimePoint m_currentTime;
            float m_deltaTime;
            float m_elapsedTime;
            float m_elapsedUnscaledTime;
            U64 m_timeFrame;

        public:
            float timeScale;
            bool isPaused;

            Clock();

            Clock& operator=(const Clock& inClock) = delete;
            Clock& operator=(Clock&& inClock) = delete;

            void UpdateTime();
            float GetDeltaTime() const;
            float GetElapsedTime() const;
            float GetElapsedUnscaledTime() const;

            U64 GetTimeFrame() const;

            static U64 GetTimestamp();
    };
}
