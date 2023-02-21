#include "World.h"

World::World()
{
	background = { 0.37, 0.63, 0.76 };
	mainCamera = new kwee::Camera(glm::vec4(0, 0, kwee::Application::getInstance()->getWindowSize()));
	mainCamera->setScale(glm::vec2(0.1f, 0.1f));

	grid = new Grid{ 250 };
	addObject(grid);

	phantomArrow = new kwee::GameObject("wire_active");
	phantomArrow->alpha = 0.0;
	phantomArrow->mix = 0.2;
	phantomArrow->color = {1.0, 1.0, 1.0};
	phantomArrow->visible = false;
	addObject(phantomArrow);
}

World::~World()
{
	delete grid;
}