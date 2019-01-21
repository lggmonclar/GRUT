#pragma once
#include "grutpch.h"

namespace GRUT {
  enum class JobPriority {
    LOW, NORMAL, HIGH, CRITICAL
  };

  struct Job {
    using EntryPoint = std::function<void()>;
    friend class JobManager;
  private:
    int                m_id = -1;
    EntryPoint         m_entryPoint = nullptr;
    uintptr_t          m_param;
    JobPriority        m_priority;
    std::atomic<bool>  m_isDone = false;
    std::atomic<int>   m_counter = 0;
    void*              m_associatedFiber;
  public:
    explicit Job(EntryPoint p_entryPoint) : m_entryPoint(p_entryPoint) {}
    explicit Job(EntryPoint p_entryPoint, int p_id) : m_entryPoint(p_entryPoint), m_id(p_id) {}
    explicit Job(EntryPoint p_entryPoint, uintptr_t p_param, JobPriority p_priority) : m_entryPoint(p_entryPoint), m_param(p_param), m_priority(p_priority) {}
    ~Job() = default;
    Job(Job &&old) :
      m_entryPoint(old.m_entryPoint), m_param(old.m_param),
      m_priority(old.m_priority), m_id(old.m_id), m_associatedFiber(old.m_associatedFiber)
    { 
      if (this != &old) {
        m_isDone.store(old.m_isDone);
        m_counter.store(old.m_counter);
        old.m_entryPoint = nullptr;
        old.m_associatedFiber = nullptr;
        old.m_isDone = false;
        old.m_counter = 0;
        old.m_id = -1;
      }
    }
    Job& operator=(Job &&old) {
      if (this != &old) {
        m_entryPoint = old.m_entryPoint;
        m_param = old.m_param;
        m_priority = old.m_priority;
        m_isDone.store(old.m_counter);
        m_counter.store(old.m_counter);
        m_id = old.m_id;
        m_associatedFiber = old.m_associatedFiber;

        old.m_associatedFiber = nullptr;
        old.m_entryPoint = nullptr;
        old.m_counter = 0;
        old.m_id = -1;
      }

      return *this;
    }
    Job(const Job&) = delete;
    Job& operator=(Job const&) = delete;
  };
}