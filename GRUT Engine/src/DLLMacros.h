#pragma once

#ifdef GRUT_PLATFORM_WINDOWS
	#ifdef GRUT_BUILD_DLL
		#define GRUT_API __declspec(dllexport)
	#else
		#define	GRUT_API __declspec(dllimport)
	#endif
#endif