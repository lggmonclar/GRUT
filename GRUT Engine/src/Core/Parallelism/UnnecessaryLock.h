#pragma once
#include <cassert>

//Source: Game Engine Architecture 3rd Edition, Pg. 327
namespace GRUT {
  class UnnecessaryLock {
  private:
    volatile bool m_locked;
  public:
    void Acquire() {
      //assert no one already has the lock
      assert(!m_locked);

      //now lock (so we can detect overlapping critical operations if they happen)
      m_locked = true;
    }

    void Release() {
      //assert correct usage (that Release() is only called after Acquire())
      assert(m_locked);

      //unlock
      m_locked = false;
    }
  };

  #if GRUT_DEBUG
    #define BEGIN_ASSERT_LOCK_NOT_NECESSARY(L) (L).Acquire()
    #define END_ASSERT_LOCK_NOT_NECESSARY(L) (L).Release()
  #else
    #define BEGIN_ASSERT_LOCK_NOT_NECESSARY(L)
    #define END_ASSERT_LOCK_NOT_NECESSARY(L)
  #endif
}