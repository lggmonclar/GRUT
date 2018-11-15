#include "Job.h"
#include "JobManager.h"

namespace GRUT {
	/*Public:*/
	const void Job::WaitForJob(const std::weak_ptr<Job> p_weakJobPtr) {
		JobManager::Instance().PlaceFiberOnWaitList(p_weakJobPtr, this);
	}

	const void Job::WaitForJobs(const std::initializer_list<std::weak_ptr<Job>> p_weakJobPtrs) {
		JobManager::Instance().PlaceFibersOnWaitList(p_weakJobPtrs, this);
	}
}
