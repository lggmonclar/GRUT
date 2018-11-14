#pragma once
#include <thread>
#include <atomic>

//Source: Game Engine Architecture 3rd Edition, Pg. 319
class SpinLock {
	std::atomic_flag m_atomic;
public:
	SpinLock() : m_atomic() {}
	bool TryAcquire() {
		// use an acquire fence to ensure all subsequent
		// reads by this thread will be valid
		bool alreadyLocked = m_atomic.test_and_set(std::memory_order_acquire);
		return !alreadyLocked;
	}
	void Acquire() {
		// spin until successful acquire
		while (!TryAcquire()) {
			// reduce power consumption on Intel CPUs
			// (can substitute with std::this_thread::yield()
			// on platforms that don't support CPU pause, if
			// thread contention is expected to be high)
			//PAUSE();
			std::this_thread::yield();
		}
	}
	void Release() {
		// use release semantics to ensure that all prior
		// writes have been fully committed before we unlock
		m_atomic.clear(std::memory_order_release);
	}
};