#pragma once
#pragma message("Compiling precompiled headers.\n")
#include <iostream>

#include <thread>
#include <atomic>

#include <vector>
#include <queue>
#include <map>

#ifdef GRUT_PLATFORM_WINDOWS
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
#endif