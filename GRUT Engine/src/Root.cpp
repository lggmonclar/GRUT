#include "grutpch.h"
#include "Root.h"
#include "Core/Timing/Clock.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Jobs/Job.h"
#include "Input/InputManager.h"
#include "Graphics/Windows/GLWindow.h"
#include "Scene/SceneManager.h"

namespace GRUT {
  int i = 0;

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
    GetGameClock().UpdateTime();
    double lag = 0.0;

    while(!window->ShouldClose()) {
      lag += GetGameClock().GetDeltaTime();

      //Poll inputs in main thread
      inputManager.PollInputs();

      //Update Scene
      while (lag >= MS_PER_UPDATE) {
        SceneManager::Instance().FixedUpdate(MS_PER_UPDATE);
        lag -= MS_PER_UPDATE;
      }

      float deltaTime = GetGameClock().GetDeltaTime();
      SceneManager::Instance().Update(deltaTime);

      //Render in worker threads
      renderManager.DrawFrame();

      //Defragment up to n blocks of memory
      MemoryManager::Instance().Defragment(10);
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