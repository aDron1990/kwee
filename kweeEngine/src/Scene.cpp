#include "kwee/game_primitives/Scene.h"

kwee::Scene::Scene()
{
	objects_ = std::vector<GameObject*>();
}

kwee::Scene::~Scene()
{
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->destroy();
	}
}

void kwee::Scene::draw()
{
	mainCamera_->useViewport();
	glm::mat4 viewProjectionMatrix = mainCamera_->getViewProjectionMatrix();
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->draw(viewProjectionMatrix);
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
		if (objects_[i] == object);
		objects_.erase(objects_.begin() + i, objects_.begin() + i + 1);
	}
}