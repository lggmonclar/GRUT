#include "grutpch.h"
#include "Root.h"
#include "JobManager.h"
#include "InputManager.h"
#include "MemoryManager.h"
#include "Job.h"
#include "windows/GLWindow.h"

namespace GRUT {
  int i = 0;

  Root::Root() {
    window = InitializeWindow();
    Logger::Initialize();
    renderManager.SetWindow(window);
    inputManager.SetWindow(window);
    JobManager::Instance();
  }

  Root::~Root() {
  }

  void Root::Run() {
    while(!window->ShouldClose()) {
      //Poll inputs in main thread
      inputManager.PollInputs();
      //Render in worker threads
      JobManager::Instance().KickJob(Job([=](std::shared_ptr<Job> p) {
        Timer t("Render");
        renderManager.Draw();
      }));
    }
  }
  const std::shared_ptr<Window> Root::InitializeWindow() {
    return std::shared_ptr<Window>(new GLWindow());
  }
}