#pragma once
#include "DLLMacros.h"
#include "Input/InputManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Config/CVar.h"

namespace GRUT {
    class Engine {
        public:
            Engine();
            virtual ~Engine();
            void Run();
            static class Clock& GetGameClock();

        private:
            std::shared_ptr<IWindow> m_window;
            FrameParams* m_frames;
            const std::shared_ptr<IWindow> InitializeWindow();
    };
}