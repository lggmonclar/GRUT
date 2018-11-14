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
			Declaration(Declaration &&old) : 
				m_entryPoint(old.m_entryPoint), m_param(old.m_param),
				m_priority(m_priority), m_counter(old.m_counter) 
			{	
				if (this != &old) {
					old.m_entryPoint = nullptr;
					old.m_counter = nullptr;
				}
			}
			Declaration& operator=(Declaration &&old) { 
				if (this == &old) return *this;

				m_entryPoint = old.m_entryPoint;
				m_param = old.m_param;
				m_priority = old.m_priority;
				m_counter = old.m_counter;

				old.m_entryPoint = nullptr;
				old.m_counter = nullptr;
			}
			Declaration(const Declaration&) = delete;
			Declaration& operator=(Declaration const&) = delete;

			EntryPoint* m_entryPoint;
			uintptr_t	m_param;
			Priority	m_priority;
			Counter*	m_counter;
		};
	}
}