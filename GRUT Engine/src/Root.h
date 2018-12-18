#pragma once
#include "grutpch.h"
#include "Job.h"
#include "DLLMacros.h"
#include "RenderManager.h"
#include "InputManager.h"

namespace GRUT {
	class Root {
	private:
		RenderManager	renderManager;
		InputManager	inputManager;
	public:
		GRUT_API Root();
		GRUT_API virtual ~Root();
		GRUT_API const void Run();
		GRUT_API const std::shared_ptr<Window> InitializeWindow();
	};

	Root* CreateApplication();
}