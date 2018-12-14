#pragma once

#include "src/Root.h"
#include "src/Job.h"

#pragma once

#ifdef GRUT_PLATFORM_WINDOWS

extern GRUT::Root* GRUT::CreateApplication();

int main(int argc, char** argv) {
	auto app = GRUT::CreateApplication();
	app->Run();
	delete app;
}

#endif