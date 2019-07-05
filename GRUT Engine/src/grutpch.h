#pragma once
#pragma message("Compiling precompiled headers.\n")

#include "Core/Debugging/Logger.h"
#include "Core/Timing/Timer.h"

#include <thread>
#include <atomic>

#include <chrono>

#include <vector>
#include <queue>
#include <unordered_map>
#include <map>

#include <fstream>
#include <sstream>
#include <iostream>

#include <sid/sid.h>

#include "GRUTMath.h"

#include <imgui.h>
#ifndef IMGUI_IMPL_OPENGL_LOADER_GLAD
  #define IMGUI_IMPL_OPENGL_LOADER_GLAD
  #include <examples/imgui_impl_opengl3.h>
  #include <examples/imgui_impl_glfw.h>
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
  #define STB_IMAGE_IMPLEMENTATION
#endif

#ifdef GRUT_PLATFORM_WINDOWS
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <Windows.h>
  #include <glad/glad.h>
  #include <GLFW/glfw3.h>
#endif