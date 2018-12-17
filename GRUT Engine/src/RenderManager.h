#pragma once
#include <GLAD/include/glad/glad.h>
#include <GLFW/glfw3.h>

namespace GRUT {
	class RenderManager {
	private:
		GLFWwindow * window;
	protected:
		RenderManager();
		~RenderManager();
	public:
		RenderManager(RenderManager const &) = delete;
		RenderManager& operator=(RenderManager const &) = delete;
		static RenderManager& Instance() {
			static RenderManager instance{};
			return instance;
		}
		void Draw();
	};
};