#pragma once
#include "grutpch.h"
#include "SpinLock.h"
#include "DLLMacros.h"

namespace GRUT {
	enum class GRUT_API JobPriority {
		LOW, NORMAL, HIGH, CRITICAL
	};

	class Job {
		using EntryPoint = std::function<void(std::shared_ptr<Job> param)>;
		friend class JobManager;
	private:
		int														m_id = -1;
		EntryPoint												m_entryPoint = nullptr;
		uintptr_t												m_param;
		JobPriority												m_priority;
		std::atomic<bool>										m_isDone = false;
		std::atomic<int>										m_counter = 0;
		void*													m_associatedFiber;
	public:
		GRUT_API explicit Job(EntryPoint p_entryPoint) : m_entryPoint(p_entryPoint) {}
		GRUT_API explicit Job(EntryPoint p_entryPoint, int p_id) : m_entryPoint(p_entryPoint), m_id(p_id) {}
		GRUT_API explicit Job(EntryPoint p_entryPoint, uintptr_t p_param, JobPriority p_priority) : m_entryPoint(p_entryPoint), m_param(p_param), m_priority(p_priority) {}
		GRUT_API ~Job() = default;
		GRUT_API Job(Job &&old) :
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
		GRUT_API Job& operator=(Job &&old) {
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
		GRUT_API Job(const Job&) = delete;
		GRUT_API Job& operator=(Job const&) = delete;

		const void GRUT_API WaitForJob(const std::weak_ptr<Job> p_weakJobPtr);
		const void GRUT_API WaitForJobs(const std::initializer_list<std::weak_ptr<Job>> p_weakJobPtrs);
	};
}