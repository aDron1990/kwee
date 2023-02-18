#include "PlayerController.h"
#include "Cube.h"

#include <kwee/game_primitives/GameObject.h>
#include <kwee/systems/Input.h>
#include <kwee/systems/PhysicEngine.h>
#include <glm/glm.hpp>
#include <iostream>


Cube* PlayerController::controlled[2] = {0, 0};
float PlayerController::cubeSpeed = 0.001f;

void PlayerController::update()
{
	for (int i = 0; i < 2; i++)
	{
		if (controlled[i]->controlled)
		{
			int delta = kwee::PhysicEngine::getDelta();
			glm::vec2 pos = controlled[i]->getPosition();
			float angle = controlled[i]->getRotation();

			if (kwee::Input::getKey('W')) pos.y += (float)cubeSpeed * kwee::PhysicEngine::getDelta();
			if (kwee::Input::getKey('S')) pos.y -= (float)cubeSpeed * kwee::PhysicEngine::getDelta();
			if (kwee::Input::getKey('D')) pos.x += (float)cubeSpeed * kwee::PhysicEngine::getDelta();
			if (kwee::Input::getKey('A')) pos.x -= (float)cubeSpeed * kwee::PhysicEngine::getDelta();

			if (kwee::Input::getKey('Q')) angle += (float)0.05 * kwee::PhysicEngine::getDelta();
			if (kwee::Input::getKey('E')) angle -= (float)0.05 * kwee::PhysicEngine::getDelta();

			controlled[i]->setPosition(pos);
			controlled[i]->setRotation(angle);
		}
	}
}

void PlayerController::switchPlayers()
{
	for (int i = 0; i < 2; i++)
	{
		controlled[i]->controlled = !controlled[i]->controlled;
	}
}