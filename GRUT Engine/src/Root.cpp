#include "grutpch.h"
#include "Root.h"
#include "MemoryManager.h"
#include "JobManager.h"
#include "RenderManager.h"
#include "Job.h"

namespace GRUT {
	int i = 0;

	Root::Root() {
		JobManager::Instance();
		RenderManager::Instance();
	}

	Root::~Root() {
	}

	const void Root::Run() {
		//auto func = [&](int group) {
		//	auto j1 = JobManager::Instance().KickJob(Job([=](std::shared_ptr<Job> p) {
		//		std::cout << "X" << group << "\n";
		//	}, ++i));
		//	auto j2 = JobManager::Instance().KickJob(Job([=](std::shared_ptr<Job> p) {
		//		p->WaitForJob(j1);
		//		std::cout << "Y" << group << "\n";
		//	}, ++i));
		//	auto j3 = JobManager::Instance().KickJob(Job([=](std::shared_ptr<Job> p) {
		//		p->WaitForJob(j2);
		//		std::cout << "Z" << group << "\n";
		//	}, ++i));
		//	auto j4 = JobManager::Instance().KickJob(Job([=](std::shared_ptr<Job> p) {
		//		p->WaitForJob(j3);
		//		std::cout << "W" << group << "\n";
		//	}, ++i));
		//	auto j5 = JobManager::Instance().KickJob(Job([=](std::shared_ptr<Job> p) {
		//		p->WaitForJobs({ j1, j2, j3, j4 });
		//		std::cout << "ALL" << group << "\n";
		//	}, ++i));
		//};

		//for (int j = 0; j < 10000; j++) {
		//	func(j);
		//	std::this_thread::sleep_for(std::chrono::seconds(1));
		//}
		while (true) {
			RenderManager::Instance().Draw();
		}
	}
}