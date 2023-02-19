#pragma once

#include "kwee/core/api.h"
#include "Input.h"
#include "kwee/game_primitives/Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace kwee
{
	class KWEEAPI Application
	{
	private:

		static Application* instance_;
		bool runing_;
		Scene* activeScene_;
		glm::vec2 windowSize_;

	protected:

		GLFWwindow* window;

	public:


		GLuint vbo_, vao_, ebo_;


		Application(glm::vec2 windowSize, bool allocConsole);
		virtual ~Application();
		static Application* getInstance();

		void run();
		void loadScene(Scene* scene);
		void render();

		virtual void update(){};

		Scene* getScene();
		glm::vec2 getWindowSize();
	};

	extern kwee::Application* CreateApplication();
}