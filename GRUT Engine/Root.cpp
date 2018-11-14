#include "Root.h"
#include "Singleton.h"
#include "MemoryManager.h"
#include "JobManager.h"
#include <thread>

namespace GRUT {
	void test1(uintptr_t params);
	void test2(uintptr_t params);
	void test3(uintptr_t params);
	void test4(uintptr_t params);


	Root::Root() {
		Singleton<MemoryManager>::Instance();
		Singleton<JobManager>::Instance();

		Job::Declaration d1;
		Job::Declaration d2;
		Job::Declaration d3;
		Job::Declaration d4;

		d1.m_entryPoint = test1;
		d2.m_entryPoint = test2;
		d3.m_entryPoint = test3;
		d4.m_entryPoint = test4;
		Singleton<JobManager>::Instance().KickJob(std::move(d1));
		Singleton<JobManager>::Instance().KickJob(std::move(d2));
		Singleton<JobManager>::Instance().KickJob(std::move(d3));
		Singleton<JobManager>::Instance().KickJob(std::move(d4));
	}

	const void Root::RunGameLoop() {
		while (true) {

		}
	}

	Root::~Root() {
	}

	void test1(uintptr_t params) {
		std::cout << "TEST1!" << std::endl;
	}
	void test2(uintptr_t params) {
		std::cout << "TWO!" << std::endl;
	}
	void test3(uintptr_t params) {
		std::cout << "3!" << std::endl;
	}
	void test4(uintptr_t params) {
		std::cout << "FAWH!" << std::endl;
	}
}