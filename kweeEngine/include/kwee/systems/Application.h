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

	protected:

		GLFWwindow* window;

	public:


		GLuint vbo_, vao_, ebo_;


		Application();
		virtual ~Application();
		static Application* getInstance();

		void run();
		void loadScene(Scene* scene);
		void render();

		virtual void update(){};

		Scene* getScene();
	};

	extern kwee::Application* CreateApplication();
}