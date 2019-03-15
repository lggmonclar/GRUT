#include "grutpch.h"
#include "Root.h"
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

namespace GRUT {
  Root::Root() {
    MemoryManager::Initialize();
    Logger::Initialize();
    PhysicsManager::Initialize();
    JobManager::Initialize();
    SceneManager::Initialize();
    window = InitializeWindow();
    RenderManager::Initialize(window);
    InputManager::Initialize(window);
    GetGameClock();
  }

  Root::~Root() {
    JobManager::Instance().Destroy();
  }

  void Root::Run() {
    int guardIndex = 0;
    int prevIndex = 2;
    int currIndex = 3;
    while(!window->ShouldClose()) {
      while (!frames[guardIndex].isDone) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
      }
      GetGameClock().UpdateTime();
      frames[currIndex].isDone = false;
      frames[currIndex].deltaTime = GetGameClock().GetDeltaTime();

      //Poll inputs in main thread
      InputManager::Instance().PollInputs();

      //Do physics frame
      PhysicsManager::Instance().Update(frames[prevIndex], frames[currIndex]);

      //Update Scene in worker threads
      SceneManager::Instance().Update(frames[prevIndex], frames[currIndex]);

      //Render in worker threads
      RenderManager::Instance().DrawFrame(frames[prevIndex], frames[currIndex]);

      //Defragment up to n blocks of memory in worker threads
      MemoryManager::Instance().Defragment(frames[prevIndex], frames[currIndex]);

      //Increment relevant frame indices
      guardIndex = (guardIndex + 1) % 16;
      prevIndex = (prevIndex + 1) % 16;
      currIndex = (currIndex + 1) % 16;
    }
  }
  const std::shared_ptr<Window> Root::InitializeWindow() {
    return std::shared_ptr<Window>(new GLWindow());
  }

  Clock& Root::GetGameClock() {
    static Clock clock{};
    return clock;
  }
}