#pragma once
#include <functional>
#include <atomic>

namespace GRUT {
  enum class JobPriority {
    LOW, NORMAL, HIGH, CRITICAL
  };

  struct Job {
    //using EntryPoint = std::function<void()>;
    friend class JobManager;
  private:
    std::function<void()> m_entryPoint = nullptr;
    std::atomic<bool>     m_isDone = false;
    std::atomic<int>      m_counter = 0;
    void*                 m_associatedFiber;
  public:
    template <typename EntryPoint = std::function<void()>>
    Job(EntryPoint p_entryPoint) : m_entryPoint(p_entryPoint) {}
    ~Job() = default;
    Job(Job &&old) :
      m_entryPoint(old.m_entryPoint),
      m_associatedFiber(old.m_associatedFiber)
    { 
      if (this != &old) {
        m_isDone.store(old.m_isDone);
        m_counter.store(old.m_counter);
        old.m_entryPoint = nullptr;
        old.m_associatedFiber = nullptr;
        old.m_isDone = false;
        old.m_counter = 0;
      }
    }
    Job& operator=(Job &&old) {
      if (this != &old) {
        m_entryPoint = old.m_entryPoint;
        m_isDone.store(old.m_counter);
        m_counter.store(old.m_counter);
        m_associatedFiber = old.m_associatedFiber;

        old.m_associatedFiber = nullptr;
        old.m_entryPoint = nullptr;
        old.m_counter = 0;
      }

      return *this;
    }
    Job(const Job&) = delete;
    Job& operator=(Job const&) = delete;
  };
}