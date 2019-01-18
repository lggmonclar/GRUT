#include "grutpch.h"
#include "Root.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Timing/Clock.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Jobs/Job.h"
#include "Input/InputManager.h"
#include "Graphics/Windows/GLWindow.h"
#include "Scene/SceneManager.h"

namespace GRUT {
  Root::Root() {
    MemoryManager::Initialize();
    Logger::Initialize();
    JobManager::Initialize();
    SceneManager::Initialize();
    window = InitializeWindow();
    renderManager.Initialize(window);
    inputManager.Initialize(window);
    GetGameClock();
  }

  Root::~Root() {
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
      inputManager.PollInputs();

      //Update Scene
      //LOG_DEBUG("lag {0}", lag);
      //while (lag >= MS_PER_UPDATE) {
      //SceneManager::Instance().FixedUpdate(MS_PER_UPDATE);
      //  lag -= MS_PER_UPDATE;
      //}
      SceneManager::Instance().Update(frames[prevIndex], frames[currIndex]);

      //Render in worker threads
      renderManager.DrawFrame(frames[prevIndex], frames[currIndex]);

      //Defragment up to n blocks of memory
      MemoryManager::Instance().Defragment(frames[prevIndex], frames[currIndex]);
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