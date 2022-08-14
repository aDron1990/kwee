#define KWEE_APPLICATION

#include "TestScene.h"
#include "PlayerController.h"

#include <kwee/kwee.h>
#include <kwee/systems/PhysicEngine.h>
#include <iostream>

using kwee::Input;



class TestGame : public kwee::Application
{
public:

	TestScene* scene;

	TestGame()
	{
		kwee::ResourceManager::loadShader("res/shaders/test_v.glsl", "res/shaders/test_f.glsl", "testShader");
		scene = new TestScene;
		loadScene(scene);
		std::cout << kwee::PhysicEngine::cross(0, 0, 0, 2, 1, 0, 1, 2) << std::endl;
	}

	~TestGame()
	{

	}

	void update() override
	{
		PlayerController::update();
	}
};

kwee::Application* kwee::CreateApplication()
{
	return new TestGame;
}