#include "grutpch.h"
#include "Clock.h"

namespace GRUT {
  Clock::Clock()
    : m_startTime{ HighResClock::now() },
    m_currentTime{ HighResClock::now() },
    m_deltaTime{},
    m_elapsedTime(0),
    m_elapsedUnscaledTime(0),
    m_timeFrame{ 0 },
    timeScale{ 1.f },
    isPaused{ false } {}

  void Clock::UpdateTime() {
    m_timeFrame++;
    m_deltaTime = 0.0;
    if (!isPaused) {
      TimePoint newTime = HighResClock::now();
      Nanoseconds delta =
        std::chrono::duration_cast<Nanoseconds>(newTime - m_currentTime);
      Nanoseconds elapse =
        std::chrono::duration_cast<Nanoseconds>(newTime - m_startTime);

      m_currentTime = newTime;
      m_deltaTime = delta.count() * 1e-9 * timeScale;
      m_elapsedTime += m_deltaTime;
      m_elapsedUnscaledTime = elapse.count() * 1e-9;
    }
  }

  double Clock::GetDeltaTime() const { return m_deltaTime; }
  double Clock::GetElapsedTime() const { return m_elapsedTime; }
  double Clock::GetElapsedUnscaledTime() const { return m_elapsedUnscaledTime; }
  U64 Clock::GetTimeFrame() const { return m_timeFrame; }

  U64 Clock::GetTimestamp() {
    U64 unixTimestamp = std::chrono::seconds(std::time(nullptr)).count();
    return unixTimestamp;
  }
}