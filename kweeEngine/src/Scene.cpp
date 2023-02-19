#include "kwee/game_primitives/Scene.h"

#include <iostream>

kwee::Scene::Scene()
{
	objects_ = std::vector<GameObject*>();
}

kwee::Scene::~Scene()
{
	//for (int i = 0; i < objects_.size(); i++)
	//{
	//	objects_[i]->destroy();
	//}
}

void kwee::Scene::draw()
{
	mainCamera_->useViewport();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(background.red, background.green, background.blue, 1.0);
	glm::mat4 viewMatrix = mainCamera_->getViewMatrix();
	glm::mat4 projectionMatrix = mainCamera_->getProjectionMatrix();
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->draw(viewMatrix, projectionMatrix);
	}
}

void kwee::Scene::update()
{
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->update();
	}
}

void kwee::Scene::addObject(GameObject* object)
{
	objects_.push_back(object);
	object->setOwnerScene(this);
}

void kwee::Scene::removeObject(GameObject* object)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i] == object)
		{ 
			std::cout << i << std::endl;
			objects_.erase(objects_.begin() + i, objects_.begin() + i + 1);
		}
	}
}

kwee::Camera* kwee::Scene::getCamera()
{
	return mainCamera_;
}