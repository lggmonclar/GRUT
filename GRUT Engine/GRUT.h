#pragma once
#include "src/Root.h"
#include "src/Scene/GameObject.h"
#include "src/Scene/Components/Component.h"
#include "src/Scene/Components/RenderableComponent.h"

#ifdef GRUT_PLATFORM_WINDOWS

extern GRUT::Root* GRUT::CreateApplication();

int main(int argc, char** argv) {
  auto app = GRUT::CreateApplication();
  app->Run();
  delete app;
}

#endif