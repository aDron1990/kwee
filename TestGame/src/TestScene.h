#pragma once

#include "Cube.h"
#include "PlayerController.h"

#include <kwee/game_primitives/Scene.h>

class TestScene : public kwee::Scene
{
	friend class TestGame;
public:

	Cube* c1;
	Cube* c2;

	TestScene()
	{
		PlayerController::controlled[0] = new Cube(true);
		PlayerController::controlled[1] = new Cube(false);

		PlayerController::controlled[0]->createCollider(1, 0);
		PlayerController::controlled[1]->createCollider(1, 0);

		PlayerController::controlled[0]->setPosition(glm::vec2(2, 0));
		PlayerController::controlled[0]->setScale(glm::vec2(2, 1));
		PlayerController::controlled[1]->setScale(glm::vec2(1, 3));
		PlayerController::controlled[0]->colliderIsDrawing = true;
		PlayerController::controlled[1]->colliderIsDrawing = true;

		addObject(PlayerController::controlled[0]);
		addObject(PlayerController::controlled[1]);

		mainCamera_ = new kwee::Camera(glm::vec4(0, 0, 800, 600));
		mainCamera_->setScale(glm::vec2(0.1f, 0.1f));
	}

	~TestScene()
	{

	}

};