#pragma once
#include <stdint.h>
#include <optional>

namespace GRUT {
	namespace Job {
		typedef void EntryPoint(uintptr_t param);

		enum class Priority {
			LOW, NORMAL, HIGH, CRITICAL
		};

		struct Counter {
			unsigned int val;
		};

		struct Declaration {
		private:
		public:
			EntryPoint* m_entryPoint = nullptr;
			uintptr_t	m_param;
			Priority	m_priority;
			Counter*	m_counter;
		};
	}
}