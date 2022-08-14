#include "PlayerController.h"
#include "Cube.h"

#include <kwee/game_primitives/GameObject.h>
#include "kwee/systems/Input.h"
#include <glm/glm.hpp>

Cube* PlayerController::controlled[2] = {0, 0};
float PlayerController::cubeSpeed = 0.08f;

void PlayerController::update()
{
	for (int i = 0; i < 2; i++)
	{
		if (controlled[i]->controlled)
		{
			glm::vec2 pos = controlled[i]->getPosition();
			float angle = controlled[i]->getRotation();

			if (kwee::Input::getKey('W')) pos.y += cubeSpeed;
			if (kwee::Input::getKey('S')) pos.y -= cubeSpeed;
			if (kwee::Input::getKey('D')) pos.x += cubeSpeed;
			if (kwee::Input::getKey('A')) pos.x -= cubeSpeed;

			if (kwee::Input::getKey('Q')) angle += 0.5;
			if (kwee::Input::getKey('E')) angle -= 0.5;

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