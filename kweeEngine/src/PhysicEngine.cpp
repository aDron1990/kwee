#include "kwee/systems/PhysicEngine.h"
#include "kwee/game_primitives/GameObject.h"

std::vector<kwee::Collider*> kwee::PhysicEngine::colliders_ = std::vector<kwee::Collider*>();
std::vector<int>  kwee::PhysicEngine::requiedToRemoveCollidersIds_ = std::vector<int>();

void kwee::PhysicEngine::addCollider(Collider* c)
{
	colliders_.push_back(c);
}

void kwee::PhysicEngine::removeCollider(Collider* c)
{
	for (int i = 0; i < colliders_.size(); i++)
	{
		if (colliders_[i] == c)
		{
			requiedToRemoveCollidersIds_.push_back(i);
		}
	}
}

void kwee::PhysicEngine::update()
{
	for (int i = 0; i < colliders_.size(); i++)
	{
		for (int j = i + 1; j < colliders_.size(); j++)
		{
			if (checkCollisions(colliders_[i], colliders_[j]) || checkCollisions(colliders_[j], colliders_[i]))
			{
				if (colliders_[i]->lastUpdateHaveCollision == false)
				{
					colliders_[i]->onCollisionEnter(colliders_[j]);
					colliders_[j]->onCollisionEnter(colliders_[i]);
				}

				colliders_[i]->onCollision(colliders_[j]);
				colliders_[j]->onCollision(colliders_[i]);

				colliders_[i]->lastUpdateHaveCollision = true;
				colliders_[j]->lastUpdateHaveCollision = true;
			}
			else
			{
				if (colliders_[i]->lastUpdateHaveCollision == true)
				{
					colliders_[i]->onCollisionExit(colliders_[j]);
					colliders_[j]->onCollisionExit(colliders_[i]);

					colliders_[i]->lastUpdateHaveCollision = false;
					colliders_[j]->lastUpdateHaveCollision = false;
				}
			}
		}
	}

	removeRequiedObjects();
}

bool kwee::PhysicEngine::checkCollisions(Collider* c1, Collider* c2)
{
	Rect rect;
	glm::mat4 tr = c1->owner_->getTransformMatrix();
	rect.v11 = tr * glm::vec4(c1->vertices_[0], c1->vertices_[1], 0.0f, 1.0f);
	rect.v12 = tr * glm::vec4(c1->vertices_[2], c1->vertices_[3], 0.0f, 1.0f);
	rect.v21 = tr * glm::vec4(c1->vertices_[4], c1->vertices_[5], 0.0f, 1.0f);
	rect.v22 = tr * glm::vec4(c1->vertices_[6], c1->vertices_[7], 0.0f, 1.0f);

	tr = c2->owner_->getTransformMatrix();
	glm::vec2 v11 = tr * glm::vec4(c2->vertices_[0], c2->vertices_[1], 0.0f, 1.0f);
	glm::vec2 v12 = tr * glm::vec4(c2->vertices_[2], c2->vertices_[3], 0.0f, 1.0f);
	glm::vec2 v21 = tr * glm::vec4(c2->vertices_[4], c2->vertices_[5], 0.0f, 1.0f);
	glm::vec2 v22 = tr * glm::vec4(c2->vertices_[6], c2->vertices_[7], 0.0f, 1.0f);

	if (isPointInRect(v11, rect)) return true;
	if (isPointInRect(v12, rect)) return true;
	if (isPointInRect(v21, rect)) return true;
	if (isPointInRect(v22, rect)) return true;

	return false;
}

bool kwee::PhysicEngine::isPointInRect(glm::vec2 point, Rect rect)
{
	if ((point.x <= rect.v11.x && point.x >= rect.v21.x) &&
		(point.y <= rect.v11.y && point.y >= rect.v21.y)) return true;
	return false;
}

void kwee::PhysicEngine::removeRequiedObjects()
{
	for (int i = 0; i < requiedToRemoveCollidersIds_.size(); i++)
	{
		colliders_[requiedToRemoveCollidersIds_[i]] = 0;
	}

	for (int i = 0; i < colliders_.size(); i++)
	{
		if (colliders_[i] == 0)
		{
			colliders_.erase(colliders_.begin() + i, colliders_.begin() + i + 1);
			i--;
		}
	}

	requiedToRemoveCollidersIds_ = std::vector<int>();
}