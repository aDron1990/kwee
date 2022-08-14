#include "kwee/systems/PhysicEngine.h"
#include "kwee/game_primitives/GameObject.h"

#include <algorithm>

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
			//if (checkCollisionsSimple(colliders_[i], colliders_[j]) || checkCollisionsSimple(colliders_[j], colliders_[i]))
			if (checkCollisions(colliders_[i], colliders_[j]))
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

bool kwee::PhysicEngine::checkCollisions(Collider* c1, Collider* c2)
{
	Rect c1Rect;
	glm::mat4 tr = c1->owner_->getTransformMatrix();
	c1Rect.v11 = tr * glm::vec4(c1->vertices_[0], c1->vertices_[1], 0.0f, 1.0f);
	c1Rect.v12 = tr * glm::vec4(c1->vertices_[2], c1->vertices_[3], 0.0f, 1.0f);
	c1Rect.v21 = tr * glm::vec4(c1->vertices_[4], c1->vertices_[5], 0.0f, 1.0f);
	c1Rect.v22 = tr * glm::vec4(c1->vertices_[6], c1->vertices_[7], 0.0f, 1.0f);

	Rect c2Rect;
	tr = c2->owner_->getTransformMatrix();
	c2Rect.v11 = tr * glm::vec4(c2->vertices_[0], c2->vertices_[1], 0.0f, 1.0f);
	c2Rect.v12 = tr * glm::vec4(c2->vertices_[2], c2->vertices_[3], 0.0f, 1.0f);
	c2Rect.v21 = tr * glm::vec4(c2->vertices_[4], c2->vertices_[5], 0.0f, 1.0f);
	c2Rect.v22 = tr * glm::vec4(c2->vertices_[6], c2->vertices_[7], 0.0f, 1.0f);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cross(c1Rect[i].x, c1Rect[i].y, c1Rect[i + 1].x, c1Rect[i + 1].y, c2Rect[j].x, c2Rect[j].y, c2Rect[j + 1].x, c2Rect[j + 1].y))
			{
				return true;
			}
		}
	}

	return false;
}

bool kwee::PhysicEngine::cross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
{
	glm::vec2 dot;
	float n;
	if (y2 - y1 != 0) 
	{
		float q = (x2 - x1) / (y1 - y2);
		float sn = (x3 - x4) + (y3 - y4) * q; 
		if (!sn) return 0;
		float fn = (x3 - x1) + (y3 - y1) * q;
		n = fn / sn;
	}
	else 
	{
		if (!(y3 - y4)) return false;
		n = (y3 - y1) / (y3 - y4);
	}

	dot.x = x3 + (x4 - x3) * n;
	dot.y = y3 + (y4 - y3) * n;

	if (((dot.x >= std::min(x1, x2) && dot.x <= std::max(x1, x2)) &&
		 (dot.y >= std::min(y1, y2) && dot.y <= std::max(y1, y2))) &&
		((dot.x >= std::min(x3, x4) && dot.x <= std::max(x3, x4)) &&
		 (dot.y >= std::min(y3, y4) && dot.y <= std::max(y3, y4))))		return true;

	if ((dot.x - x1) * (y2 - y1) - (x2 - x1) * (dot.y - y1) == 0 ||
		(dot.x - x3) * (y4 - y2) - (x4 - x2) * (dot.y - y2) == 0
		);// return true;

	return false;
}