#include "../grutpch.h"
#include "GLWindow.h"

namespace GRUT {
  GLWindow::GLWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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
      if(glWindow->m_keyboardCallback != nullptr)
        glWindow->m_keyboardCallback(KeyboardEvent());
    });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
      auto glWindow = (GLWindow*)glfwGetWindowUserPointer(window);
      if (glWindow->m_mouseCallback != nullptr)
        glWindow->m_mouseCallback(MouseEvent());
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

  void GLWindow::Draw() {
    glfwMakeContextCurrent(m_window);

    glClearColor(0.2f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_window);
    glfwMakeContextCurrent(NULL);
  }

  void GLWindow::SetKeyboardCallback(std::function<void(KeyboardEvent)> p_callback) {
    m_keyboardCallback = p_callback;
  }

  void GLWindow::SetMouseCallback(std::function<void(MouseEvent)> p_callback) {
    m_mouseCallback = p_callback;
  }

  void GLWindow::PollEvents() {
    glfwPollEvents();
  }

  bool GLWindow::ShouldClose() {
    return glfwWindowShouldClose(m_window);
  }
}
