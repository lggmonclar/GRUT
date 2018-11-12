#pragma once
#include "Singleton.h"
#include "MemoryManager.h"
#include "JobManager.h"
#include <thread>

namespace GRUT {
	class Root {
	private:
	public:
		Root();
		~Root();
		const void RunGameLoop();
	};
}