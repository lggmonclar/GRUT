#pragma once
#include <windows.h>
#include <iostream>
#include "Singleton.h"
#include "Job.h"


namespace GRUT {
	namespace Fiber {
		struct Data {
		public:
			Data() = default;
			explicit Data(LPVOID p_fiberAddr) : m_fiberAddr(p_fiberAddr){}
			operator LPVOID() { return this; }

			LPVOID m_fiberAddr;
			DWORD m_fiberResultCode;
			Job::Declaration m_currJob;
		};

		void __stdcall WaitForJob(LPVOID p_lpParameter);
	}
}