#include "grutpch.h"
#include "Engine.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Timing/Clock.h"
#include "Core/Memory/MemoryManager.h"
#include "Physics/PhysicsManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Jobs/Job.h"
#include "Input/InputManager.h"
#include "Graphics/Windows/GLWindow.h"
#include "Graphics/RenderManager.h"
#include "Scene/SceneManager.h"
#include "Core/Config/Config.h"

namespace GRUT {
  Engine::Engine() {
    GRUT::Config::Instance().Read("config.cfg");

    MemoryManager::Initialize();
    Logger::Initialize();
    PhysicsManager::Initialize();
    JobManager::Initialize();
    SceneManager::Initialize();
    m_window = InitializeWindow();
    RenderManager::Initialize(m_window);
    InputManager::Initialize(m_window);
    GetGameClock();
  }

  Engine::~Engine() {
    JobManager::Instance().Destroy();
    CVarRegistry::Destroy();
    delete[] m_frames;
  }

  void Engine::Run() {
    int frameParamsCount = GET_CVAR(CVarInt, "frame_params_count");
    m_frames = new FrameParams[frameParamsCount];

    int guardIndex = 0;
    int prevIndex = 2;
    int currIndex = 3;
    while(!m_window->ShouldClose()) {
      while (!m_frames[guardIndex].isDone) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
      }
      GetGameClock().UpdateTime();
      m_frames[currIndex].index = currIndex;
      m_frames[currIndex].isDone = false;
      m_frames[currIndex].deltaTime = GetGameClock().GetDeltaTime();

      //Poll inputs in main thread
      InputManager::Instance().PollInputs();

      //Do physics frame
      PhysicsManager::Instance().Update(m_frames[prevIndex], m_frames[currIndex]);

      //Update Scene in worker threads
      SceneManager::Instance().Update(m_frames[prevIndex], m_frames[currIndex]);

      //Render in worker threads
      RenderManager::Instance().DrawFrame(m_frames[prevIndex], m_frames[currIndex]);

      //Defragment up to n blocks of memory in worker threads
      MemoryManager::Instance().Defragment(m_frames[prevIndex], m_frames[currIndex]);

      //Increment relevant frame indices
      guardIndex = (guardIndex + 1) % frameParamsCount;
      prevIndex = (prevIndex + 1) % frameParamsCount;
      currIndex = (currIndex + 1) % frameParamsCount;
    }
  }
  const std::shared_ptr<IWindow> Engine::InitializeWindow() {
    return std::shared_ptr<IWindow>(new GLWindow());
  }

  Clock& Engine::GetGameClock() {
    static Clock clock{};
    return clock;
  }
}