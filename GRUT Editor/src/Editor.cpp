#include "Editor.h"

#ifdef GRUT_PLATFORM_WINDOWS

int main(int argc, char** argv) {
    Editor editor;

    editor.Run();

    return 0;
}

#endif

void Editor::Run() {
    Engine engine;

    m_gui.Initialize(RenderManager::Instance());

    InstanceTest();

    engine.Run();
}
