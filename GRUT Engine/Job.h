#pragma once
#include <stdint.h>
#include <optional>

namespace GRUT {
	namespace Job {
		using EntryPoint = void(uintptr_t param);

		enum class Priority {
			LOW, NORMAL, HIGH, CRITICAL
		};

		struct Counter {
			unsigned int val;
		};

		struct Declaration {
		public:
			Declaration() = default;
			Declaration(Declaration &&old) = default;
			Declaration& operator=(Declaration const&&) { return *this; };
			Declaration(const Declaration&) = delete;
			Declaration& operator=(Declaration const&) = delete;

			EntryPoint* m_entryPoint;
			uintptr_t	m_param;
			Priority	m_priority;
			Counter*	m_counter;
		};
	}
}