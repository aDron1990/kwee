#define KWEE_APPLICATION

#include "TestScene.h"
#include "PlayerController.h"

#include <kwee/kwee.h>

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