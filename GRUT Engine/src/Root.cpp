#include "grutpch.h"
#include "Root.h"
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
  }

  Root::~Root() {
  }

  void Root::Run() {
    while(!window->ShouldClose()) {
      //Poll inputs in main thread
      inputManager.PollInputs();

      //Render in worker threads
      renderManager.DrawFrame();
    }
  }
  const std::shared_ptr<Window> Root::InitializeWindow() {
    return std::shared_ptr<Window>(new GLWindow());
  }
}