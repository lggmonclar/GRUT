#pragma once
#pragma message("Compiling precompiled headers.\n")

#include "Core/Debugging/Logger.h"
#include "Core/Timing/Timer.h"

#include <thread>
#include <atomic>

#include <chrono>

#include <vector>
#include <queue>
#include <map>

#include <fstream>
#include <sstream>
#include <iostream>

#include "GRUTMath.h"

#define STB_IMAGE_IMPLEMENTATION
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef GRUT_PLATFORM_WINDOWS
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <Windows.h>
  #include <glad/glad.h>
  #include <GLFW/glfw3.h>
#endif
