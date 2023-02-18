#include "kwee/systems/Application.h" 
#include "kwee/systems/ResourceManager.h"
#include "kwee/systems/PhysicEngine.h"

kwee::Application* kwee::Application::instance_ = 0;

kwee::Application::Application()
{
	runing_ = true;
	instance_ = this;
	if(glfwInit() == 0) throw;

	window = glfwCreateWindow(800, 600, "kwee app", nullptr, nullptr);
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
	while (runing_)
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
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1, 0.2, 0.15, 1.0);
	if (activeScene_ != 0) activeScene_->draw();
}

kwee::Scene* kwee::Application::getScene()
{
	return activeScene_;
}