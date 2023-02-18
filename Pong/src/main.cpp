#include "GameScene.h"

#include <kwee/kwee.h>

class Pong : public kwee::Application
{
private:

	GameScene* sce;

	Slider* player;
	Slider* robot;
	Ball* ball;

public:

	Pong()
	{
		sce = new GameScene();

		player = new Slider;
		player->setPosition({ -12, 0 });
		player->setScale({ 0.5, 20 });

		robot = new Slider;
		robot->setPosition({ 12, 0 });

		ball = new Ball;

		sce->addObject(player);
		sce->addObject(robot);
		sce->addObject(ball);

		loadScene(sce);
	}

	~Pong()
	{
		delete sce;
	}

	void update() override
	{
#if 0
		float cubeSpeed = 0.005 / 1.5;
		glm::vec2 pos = sce->player->getPosition();
		if (kwee::Input::getKey('W')) pos.y += (float)cubeSpeed * kwee::PhysicEngine::getDelta();
		if (kwee::Input::getKey('S')) pos.y -= (float)cubeSpeed * kwee::PhysicEngine::getDelta();
		sce->player->setPosition(pos);
#else

		player->setPosition({ sce->mainCamera_->ScreenToWorld(kwee::Input::getMousePosition()).x, 0 });

#endif

		ball->move();
		glm::vec2 rp = robot->getPosition();
		glm::vec2 bp = ball->getPosition();
		robot->setPosition({ rp.x, bp.y });

		if (bp.y > 10 || bp.y < -10)
		{
			ball->changeVertDir();
			bp.y > 10 ? bp.y = 9.9 : bp.y = -9.9;
		}

		if (bp.x > 13 || bp.x < -13)
		{
			delete ball;
			ball = new Ball;
			sce->addObject(ball);
		}
	}
};

kwee::Application* kwee::CreateApplication()
{
	return new Pong;
}