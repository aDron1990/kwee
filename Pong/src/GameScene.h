#pragma once

#include "Slider.h"
#include "Ball.h"

class GameScene : public kwee::Scene
{
	friend class Pong;

private:

public:

	GameScene() : Scene()
	{
		mainCamera_ = new kwee::Camera(glm::vec4(0, 0, 800, 600));
		mainCamera_->setScale(glm::vec2(0.1f, 0.1f));
	}

	~GameScene()
	{

	}
};

