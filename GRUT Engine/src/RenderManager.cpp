#include "grutpch.h"
#include "RenderManager.h"

namespace GRUT {
	RenderManager::RenderManager() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(800, 600, "GRUT Engine", NULL, NULL);
		if (window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(-1);
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, [] (GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(-1);
		}
	}

	RenderManager::~RenderManager() {
		glfwTerminate();
	}
	void RenderManager::Draw() {
		glClearColor(0.2f, 0.6f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
