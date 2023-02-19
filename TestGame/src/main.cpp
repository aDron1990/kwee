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

	TestGame() : Application({1280, 720}, 1)
	{
		kwee::ResourceManager::loadTexture("res/textures/texture.jpg", "test");
		scene = new TestScene;
		loadScene(scene);


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