#pragma once
#include "src/Root.h"
#include "src/Graphics/Shaders/ShaderTypes.h"
#include "src/Scene/Scene.h"
#include "src/Scene/GameObjects/GameObject.h"
#include "src/Scene/Components/Component.h"
#include "src/Scene/Components/RenderableComponent.h"
#include "src/Scene/Components/Camera.h"
#include "src/Input/Input.h"

#ifdef GRUT_PLATFORM_WINDOWS

extern GRUT::Root* GRUT::CreateApplication();

int main(int argc, char** argv) {
  auto app = GRUT::CreateApplication();
  app->Run();
  delete app;
}

#endif