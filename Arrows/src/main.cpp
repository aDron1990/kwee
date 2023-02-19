#include "World.h"

#include <kwee/kwee.h>
#include <kwee/core/EntryPoint.h>
#include <cmath>
#include <iostream>

const int speeds[] = { 25, 50, 100, 250, 500, 1000, 2000 };

class Arrows : public kwee::Application
{
private:

	World* world;

	long long int lastSimulation = 0;
	int speed_i = 3;

public:

	Arrows();
	~Arrows();

	void update() override;
	void cameraInput();
	void mainInput();

	void onWindowClose();
};

kwee::Application* kwee::CreateApplication()
{
	return new Arrows;
}



Arrows::Arrows() : Application(glm::vec2{ 1280, 720 }, "Arrows", 1)
{
	kwee::ResourceManager::loadTexture("res/textures/phantom.png", "phantom");
	kwee::ResourceManager::loadTexture("res/textures/wire_active.png", "wire_active");
	kwee::ResourceManager::loadTexture("res/textures/wire_unactive.png", "wire_unactive");
	kwee::ResourceManager::loadTexture("res/textures/doublewire_active.png", "doublewire_active");
	kwee::ResourceManager::loadTexture("res/textures/doublewire_unactive.png", "doublewire_unactive");
	kwee::ResourceManager::loadTexture("res/textures/not_active.png", "not_active");
	kwee::ResourceManager::loadTexture("res/textures/not_unactive.png", "not_unactive");
	kwee::ResourceManager::loadTexture("res/textures/and_active.png", "and_active");
	kwee::ResourceManager::loadTexture("res/textures/and_unactive.png", "and_unactive");
	kwee::ResourceManager::loadTexture("res/textures/treewire_active.png", "treewire_active");
	kwee::ResourceManager::loadTexture("res/textures/treewire_unactive.png", "treewire_unactive");
	kwee::ResourceManager::loadTexture("res/textures/block_active.png", "block_active");

	world = new World;
	loadScene(world);
	lastSimulation = kwee::PhysicEngine::millis();
}

Arrows::~Arrows()
{
	delete world;
}

void Arrows::update()
{
	mainInput();
	cameraInput();
	
	if (kwee::PhysicEngine::millis() - lastSimulation > speeds[speed_i])
	{
		lastSimulation = kwee::PhysicEngine::millis();
		world->grid->simulate();
	}
}

void Arrows::cameraInput()
{
	if (kwee::Input::getMouseWheelScroll().y > 0)
		world->mainCamera->setScale(world->mainCamera->getScale() *= glm::abs((float)kwee::Input::getMouseWheelScroll().y) * 1.1);
	if (kwee::Input::getMouseWheelScroll().y < 0)
		world->mainCamera->setScale(world->mainCamera->getScale() /= glm::abs((float)kwee::Input::getMouseWheelScroll().y) * 1.1);
	if (kwee::Input::getKey(GLFW_KEY_W))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ 0, -1 } *(float)kwee::PhysicEngine::getDelta());
	if (kwee::Input::getKey(GLFW_KEY_S))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ 0,  1 } *(float)kwee::PhysicEngine::getDelta());
	if (kwee::Input::getKey(GLFW_KEY_A))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ 1,  0 } *(float)kwee::PhysicEngine::getDelta());
	if (kwee::Input::getKey(GLFW_KEY_D))
		world->mainCamera->setPosition(world->mainCamera->getPosition() +
			glm::vec2{ -1, 0 } *(float)kwee::PhysicEngine::getDelta());
}

void Arrows::mainInput()
{
	if (kwee::Input::getKeyDown(GLFW_KEY_COMMA))
	{
		sizeof(speeds) / sizeof(int);
		speed_i == sizeof(speeds) / sizeof(int) - 1 ? speed_i = sizeof(speeds) / sizeof(int) - 1 : speed_i++;
		std::cout << "simulatin speed: " << speeds[speed_i] << std::endl;
	}
	if (kwee::Input::getKeyDown(GLFW_KEY_PERIOD))
	{
		speed_i == 0 ? speed_i = 0 : speed_i--;
		std::cout << "simulatin speed: " << speeds[speed_i] << std::endl;
	}

	if (kwee::Input::getKeyDown(GLFW_KEY_1))
	{
		world->grid->at = ArrowType::Wire;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("wire_active"));
		std::cout << "selected Wire" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_2))
	{
		world->grid->at = ArrowType::DoubleWire;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("doublewire_active"));
		std::cout << "selected DoubleWire" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_3))
	{
		world->grid->at = ArrowType::Block;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("block_active"));
		std::cout << "selected Block" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_4))
	{
		world->grid->at = ArrowType::Not;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("not_active"));
		std::cout << "selected Not" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_5))
	{
		world->grid->at = ArrowType::And;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("and_active"));
		std::cout << "selected And" << std::endl;
	}
	else if (kwee::Input::getKeyDown(GLFW_KEY_6))
	{
		world->grid->at = ArrowType::TreeWire;
		world->phantomArrow->setTexture(kwee::ResourceManager::getTexture("treewire_active"));
		std::cout << "selected TreeWire" << std::endl;
	}
}

void Arrows::onWindowClose()
{
	close();
}

