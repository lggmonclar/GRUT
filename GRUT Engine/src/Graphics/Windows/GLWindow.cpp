#include "grutpch.h"
#include "GLWindow.h"
#include "Input/InputManager.h"
#include "Input/Input.h"

namespace GRUT {
  Keys TranslateKey(int p_key);
  States TranslateAction(int p_action);
  MouseButtons TranslateMouseButton(int p_button);

  GLWindow::GLWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(800, 600, "GRUT Engine", NULL, NULL);
    if (m_window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      exit(-1);
    }

    glfwMakeContextCurrent(m_window);

    //Set callback functions
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
      glViewport(0, 0, width, height);
    });
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      auto glWindow = (GLWindow*)glfwGetWindowUserPointer(window);
      InputManager::Instance().ProcessKeyboardEvent(TranslateKey(key), TranslateAction(action));
    });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
      auto glWindow = (GLWindow*)glfwGetWindowUserPointer(window);
      InputManager::Instance().ProcessMouseEvent(TranslateMouseButton(button), TranslateAction(action));
    });

    //Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      exit(-1);
    }

    //Set current context to NULL as the window context will be used by another thread after initialization
    glfwMakeContextCurrent(NULL);
  }

  GLWindow::~GLWindow() {
    glfwTerminate();
  }

  void GLWindow::SetContext() {
    BEGIN_ASSERT_LOCK_NOT_NECESSARY(m_lock);
    glfwMakeContextCurrent(m_window);
    END_ASSERT_LOCK_NOT_NECESSARY(m_lock);
  }

  void GLWindow::ClearContext() {
    BEGIN_ASSERT_LOCK_NOT_NECESSARY(m_lock);
    glfwMakeContextCurrent(NULL);
    END_ASSERT_LOCK_NOT_NECESSARY(m_lock);
  }

  void GLWindow::BeginFrame() {
    glfwMakeContextCurrent(m_window);
    glClearColor(0.2f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void GLWindow::EndFrame() {
    glfwSwapBuffers(m_window);
    glfwMakeContextCurrent(NULL);
  }

  void GLWindow::PollEvents() {
    glfwPollEvents();
  }

  bool GLWindow::ShouldClose() {
    return glfwWindowShouldClose(m_window);
  }

  Keys TranslateKey(int p_key) {
    switch (p_key) {
    case GLFW_KEY_UNKNOWN:
      return Keys::KEY_UNKNOWN;
    case GLFW_KEY_SPACE:
      return Keys::KEY_SPACE;
    case GLFW_KEY_APOSTROPHE:
      return Keys::KEY_APOSTROPHE;
    case GLFW_KEY_COMMA:
      return Keys::KEY_COMMA;
    case GLFW_KEY_MINUS:
      return Keys::KEY_MINUS;
    case GLFW_KEY_PERIOD:
      return Keys::KEY_PERIOD;
    case GLFW_KEY_SLASH:
      return Keys::KEY_SLASH;
    case GLFW_KEY_0:
      return Keys::KEY_0;
    case GLFW_KEY_1:
      return Keys::KEY_1;
    case GLFW_KEY_2:
      return Keys::KEY_2;
    case GLFW_KEY_3:
      return Keys::KEY_3;
    case GLFW_KEY_4:
      return Keys::KEY_4;
    case GLFW_KEY_5:
      return Keys::KEY_5;
    case GLFW_KEY_6:
      return Keys::KEY_6;
    case GLFW_KEY_7:
      return Keys::KEY_7;
    case GLFW_KEY_8:
      return Keys::KEY_8;
    case GLFW_KEY_9:
      return Keys::KEY_9;
    case GLFW_KEY_SEMICOLON:
      return Keys::KEY_SEMICOLON;
    case GLFW_KEY_EQUAL:
      return Keys::KEY_EQUAL;
    case GLFW_KEY_A:
      return Keys::KEY_A;
    case GLFW_KEY_B:
      return Keys::KEY_B;
    case GLFW_KEY_C:
      return Keys::KEY_C;
    case GLFW_KEY_D:
      return Keys::KEY_D;
    case GLFW_KEY_E:
      return Keys::KEY_E;
    case GLFW_KEY_F:
      return Keys::KEY_F;
    case GLFW_KEY_G:
      return Keys::KEY_G;
    case GLFW_KEY_H:
      return Keys::KEY_H;
    case GLFW_KEY_I:
      return Keys::KEY_I;
    case GLFW_KEY_J:
      return Keys::KEY_J;
    case GLFW_KEY_K:
      return Keys::KEY_K;
    case GLFW_KEY_L:
      return Keys::KEY_L;
    case GLFW_KEY_M:
      return Keys::KEY_M;
    case GLFW_KEY_N:
      return Keys::KEY_N;
    case GLFW_KEY_O:
      return Keys::KEY_O;
    case GLFW_KEY_P:
      return Keys::KEY_P;
    case GLFW_KEY_Q:
      return Keys::KEY_Q;
    case GLFW_KEY_R:
      return Keys::KEY_R;
    case GLFW_KEY_S:
      return Keys::KEY_S;
    case GLFW_KEY_T:
      return Keys::KEY_T;
    case GLFW_KEY_U:
      return Keys::KEY_U;
    case GLFW_KEY_V:
      return Keys::KEY_V;
    case GLFW_KEY_W:
      return Keys::KEY_W;
    case GLFW_KEY_X:
      return Keys::KEY_X;
    case GLFW_KEY_Y:
      return Keys::KEY_Y;
    case GLFW_KEY_Z:
      return Keys::KEY_Z;
    case GLFW_KEY_LEFT_BRACKET:
      return Keys::KEY_LEFT_BRACKET;
    case GLFW_KEY_BACKSLASH:
      return Keys::KEY_BACKSLASH;
    case GLFW_KEY_RIGHT_BRACKET:
      return Keys::KEY_RIGHT_BRACKET;
    case GLFW_KEY_GRAVE_ACCENT:
      return Keys::KEY_GRAVE_ACCENT;
    case GLFW_KEY_WORLD_1:
      return Keys::KEY_WORLD_1;
    case GLFW_KEY_WORLD_2:
      return Keys::KEY_WORLD_2;
    case GLFW_KEY_ESCAPE:
      return Keys::KEY_ESCAPE;
    case GLFW_KEY_ENTER:
      return Keys::KEY_ENTER;
    case GLFW_KEY_TAB:
      return Keys::KEY_TAB;
    case GLFW_KEY_BACKSPACE:
      return Keys::KEY_BACKSPACE;
    case GLFW_KEY_INSERT:
      return Keys::KEY_INSERT;
    case GLFW_KEY_DELETE:
      return Keys::KEY_DELETE;
    case GLFW_KEY_RIGHT:
      return Keys::KEY_RIGHT;
    case GLFW_KEY_LEFT:
      return Keys::KEY_LEFT;
    case GLFW_KEY_DOWN:
      return Keys::KEY_DOWN;
    case GLFW_KEY_UP:
      return Keys::KEY_UP;
    case GLFW_KEY_PAGE_UP:
      return Keys::KEY_PAGE_UP;
    case GLFW_KEY_PAGE_DOWN:
      return Keys::KEY_PAGE_DOWN;
    case GLFW_KEY_HOME:
      return Keys::KEY_HOME;
    case GLFW_KEY_END:
      return Keys::KEY_END;
    case GLFW_KEY_CAPS_LOCK:
      return Keys::KEY_CAPS_LOCK;
    case GLFW_KEY_SCROLL_LOCK:
      return Keys::KEY_SCROLL_LOCK;
    case GLFW_KEY_NUM_LOCK:
      return Keys::KEY_NUM_LOCK;
    case GLFW_KEY_PRINT_SCREEN:
      return Keys::KEY_PRINT_SCREEN;
    case GLFW_KEY_PAUSE:
      return Keys::KEY_PAUSE;
    case GLFW_KEY_F1:
      return Keys::KEY_F1;
    case GLFW_KEY_F2:
      return Keys::KEY_F2;
    case GLFW_KEY_F3:
      return Keys::KEY_F3;
    case GLFW_KEY_F4:
      return Keys::KEY_F4;
    case GLFW_KEY_F5:
      return Keys::KEY_F5;
    case GLFW_KEY_F6:
      return Keys::KEY_F6;
    case GLFW_KEY_F7:
      return Keys::KEY_F7;
    case GLFW_KEY_F8:
      return Keys::KEY_F8;
    case GLFW_KEY_F9:
      return Keys::KEY_F9;
    case GLFW_KEY_F10:
      return Keys::KEY_F10;
    case GLFW_KEY_F11:
      return Keys::KEY_F11;
    case GLFW_KEY_F12:
      return Keys::KEY_F12;
    case GLFW_KEY_F13:
      return Keys::KEY_F13;
    case GLFW_KEY_F14:
      return Keys::KEY_F14;
    case GLFW_KEY_F15:
      return Keys::KEY_F15;
    case GLFW_KEY_F16:
      return Keys::KEY_F16;
    case GLFW_KEY_F17:
      return Keys::KEY_F17;
    case GLFW_KEY_F18:
      return Keys::KEY_F18;
    case GLFW_KEY_F19:
      return Keys::KEY_F19;
    case GLFW_KEY_F20:
      return Keys::KEY_F20;
    case GLFW_KEY_F21:
      return Keys::KEY_F21;
    case GLFW_KEY_F22:
      return Keys::KEY_F22;
    case GLFW_KEY_F23:
      return Keys::KEY_F23;
    case GLFW_KEY_F24:
      return Keys::KEY_F24;
    case GLFW_KEY_F25:
      return Keys::KEY_F25;
    case GLFW_KEY_KP_0:
      return Keys::KEY_KP_0;
    case GLFW_KEY_KP_1:
      return Keys::KEY_KP_1;
    case GLFW_KEY_KP_2:
      return Keys::KEY_KP_2;
    case GLFW_KEY_KP_3:
      return Keys::KEY_KP_3;
    case GLFW_KEY_KP_4:
      return Keys::KEY_KP_4;
    case GLFW_KEY_KP_5:
      return Keys::KEY_KP_5;
    case GLFW_KEY_KP_6:
      return Keys::KEY_KP_6;
    case GLFW_KEY_KP_7:
      return Keys::KEY_KP_7;
    case GLFW_KEY_KP_8:
      return Keys::KEY_KP_8;
    case GLFW_KEY_KP_9:
      return Keys::KEY_KP_9;
    case GLFW_KEY_KP_DECIMAL:
      return Keys::KEY_KP_DECIMAL;
    case GLFW_KEY_KP_DIVIDE:
      return Keys::KEY_KP_DIVIDE;
    case GLFW_KEY_KP_MULTIPLY:
      return Keys::KEY_KP_MULTIPLY;
    case GLFW_KEY_KP_SUBTRACT:
      return Keys::KEY_KP_SUBTRACT;
    case GLFW_KEY_KP_ADD:
      return Keys::KEY_KP_ADD;
    case GLFW_KEY_KP_ENTER:
      return Keys::KEY_KP_ENTER;
    case GLFW_KEY_KP_EQUAL:
      return Keys::KEY_KP_EQUAL;
    case GLFW_KEY_LEFT_SHIFT:
      return Keys::KEY_LEFT_SHIFT;
    case GLFW_KEY_LEFT_CONTROL:
      return Keys::KEY_LEFT_CONTROL;
    case GLFW_KEY_LEFT_ALT:
      return Keys::KEY_LEFT_ALT;
    case GLFW_KEY_LEFT_SUPER:
      return Keys::KEY_LEFT_SUPER;
    case GLFW_KEY_RIGHT_SHIFT:
      return Keys::KEY_RIGHT_SHIFT;
    case GLFW_KEY_RIGHT_CONTROL:
      return Keys::KEY_RIGHT_CONTROL;
    case GLFW_KEY_RIGHT_ALT:
      return Keys::KEY_RIGHT_ALT;
    case GLFW_KEY_RIGHT_SUPER:
      return Keys::KEY_RIGHT_SUPER;
    case GLFW_KEY_MENU:
      return Keys::KEY_MENU;
    }
    return Keys::KEY_UNKNOWN;
  }

  States TranslateAction(int p_action) {
    switch (p_action) {
      case GLFW_PRESS:
        return States::PRESS;
      case GLFW_RELEASE:
        return States::RELEASE;
      case GLFW_REPEAT:
        return States::REPEAT;
    }
    return States::UNKNOWN;
  }

  MouseButtons TranslateMouseButton(int p_button) {
    switch (p_button) {
      case GLFW_MOUSE_BUTTON_1:
        return MouseButtons::MOUSE_1;
      case GLFW_MOUSE_BUTTON_2:
        return MouseButtons::MOUSE_2;
      case GLFW_MOUSE_BUTTON_3:
        return MouseButtons::MOUSE_3;
      case GLFW_MOUSE_BUTTON_4:
        return MouseButtons::MOUSE_4;
      case GLFW_MOUSE_BUTTON_5:
        return MouseButtons::MOUSE_5;
      case GLFW_MOUSE_BUTTON_6:
        return MouseButtons::MOUSE_6;
      case GLFW_MOUSE_BUTTON_7:
        return MouseButtons::MOUSE_7;
      case GLFW_MOUSE_BUTTON_8:
        return MouseButtons::MOUSE_8;
    }
    return MouseButtons::MOUSE_UNKNOWN;
  }
}
