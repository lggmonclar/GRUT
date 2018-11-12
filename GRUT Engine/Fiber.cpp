#include "Fiber.h"
#include "JobManager.h"

namespace GRUT {
	namespace Fiber {
		void __stdcall WaitForJob(LPVOID p_lpParameter) {
			Fiber::Data fData = (Fiber::Data)p_lpParameter;

			while (true) {
				auto job = Singleton<JobManager>::Instance().FetchJob();
				
				if (job) {
					job->m_entryPoint(job->m_param);
				}
				else {
					//std::cout << std::endl << "Fiber has no job, and job queue is empty!" << std::endl;
				}
			}
		}
	}
}
