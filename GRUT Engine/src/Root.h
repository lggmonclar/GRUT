#pragma once

#include "DLLMacros.h"

namespace GRUT {
	class GRUT_API Root {
	private:
	public:
		Root();
		virtual ~Root();
		const void Run();
	};

	Root* CreateApplication();
}