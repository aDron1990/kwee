#include "kwee/systems/Application.h" 
#include "kwee/systems/ResourceManager.h"
#include "kwee/systems/PhysicEngine.h"

#include <Windows.h>
#include <iostream>

kwee::Application* kwee::Application::instance_ = 0;
bool kwee::Application::running_ = false;

kwee::Application::Application(glm::vec2 windowSize, std::string windowName, bool allocConsole) : windowSize_(windowSize)
{
	if (!allocConsole)
	{
		HWND wnd = GetConsoleWindow();
		FreeConsole();
		PostMessage(wnd, WM_CLOSE, 0, 0);
	}

	running_ = true;
	instance_ = this;
	if(glfwInit() == 0) throw;

	glfwWindowHint(GLFW_RESIZABLE, false);

	window = glfwCreateWindow(windowSize_.x, windowSize_.y, windowName.c_str(), nullptr, nullptr);
	if (window == 0) throw;
	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0) throw;

	activeScene_ = 0;
	Input::initialize(window);
	ResourceManager::initialize();
	PhysicEngine::initialize();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

kwee::Application::~Application()
{
	ResourceManager::terminate();
	Input::terminate(window);
	glfwDestroyWindow(window);
	glfwTerminate();
}

kwee::Application* kwee::Application::getInstance()
{
	return instance_;
}

void kwee::Application::run()
{
	while (running_)
	{
		glfwPollEvents();

		
		if (activeScene_ != 0) activeScene_->update();

		PhysicEngine::removeRequiedObjects();
		PhysicEngine::update();

		update();
		render();

		glfwSwapBuffers(window);

		Input::update();
	}
}

void kwee::Application::loadScene(Scene* scene)
{
	activeScene_ = scene;
}

void kwee::Application::render()
{
	if (activeScene_ != 0) activeScene_->draw();
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1.0);
	}
}

kwee::Scene* kwee::Application::getScene()
{
	return activeScene_;
}

glm::vec2 kwee::Application::getWindowSize()
{
	return windowSize_;
}

void kwee::Application::close()
{
	running_ = false;
}