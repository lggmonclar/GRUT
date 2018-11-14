#pragma once
#include <windows.h>
#include <iostream>
#include "Job.h"


namespace GRUT {
	namespace Fiber {
		struct Data {
		public:
			Data() = default;
			explicit Data(LPVOID p_fiberAddr) : m_fiberAddr(p_fiberAddr){}
			Data(Data &&old) :
				m_fiberAddr(old.m_fiberAddr),
				m_fiberResultCode(old.m_fiberResultCode),
				m_currJob(std::move(old.m_currJob)) {
				if (this != &old) {
					old.m_fiberAddr = nullptr;
				}
			}
			Data& operator=(Data &&old) {
				if (this == &old) return *this;

				m_fiberAddr = old.m_fiberAddr;
				m_fiberResultCode = old.m_fiberResultCode;
				m_currJob = std::move(old.m_currJob);

				return *this;
			}
			Data(const Data&) = delete;
			Data& operator=(Data const&) = delete;
			operator LPVOID() { return this; }

			LPVOID m_fiberAddr;
			DWORD m_fiberResultCode;
			Job::Declaration m_currJob;
		};

		void __stdcall WaitForJob(LPVOID p_lpParameter);
	}
}