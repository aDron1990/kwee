#include "kwee/game_primitives/GameObject.h"
#include "kwee/game_primitives/Scene.h"
#include "kwee/systems/ResourceManager.h"

kwee::GameObject::GameObject(std::string meshResourñe, std::string shaderResourñe)
{
	mesh_ = ResourceManager::getMesh(meshResourñe);
	shader_ = ResourceManager::getShader(shaderResourñe);
	collider_ = 0;
}

void kwee::GameObject::destroy()
{
	owner_->removeObject(this);
	deleteCollider();
	delete this;
}

void kwee::GameObject::setOwnerScene(Scene* owner)
{
	owner_ = owner;
}

void kwee::GameObject::draw(glm::mat4 viewProjectionMatrix)
{
	shader_.use();
	shader_.setUniformMatrix4("MVP", viewProjectionMatrix * getTransformMatrix());
	mesh_.draw();
	if (collider_ != 0 && colliderIsDrawing)
	{
		Shader shader = ResourceManager::getShader("colliderShader");
		shader.use();
		shader_.setUniformMatrix4("MVP", viewProjectionMatrix * getTransformMatrix());
		collider_->draw();
	}
}

kwee::Mesh kwee::GameObject::getMesh()
{
	return mesh_;
}

void kwee::GameObject::createCollider()
{
	if (collider_ == 0) collider_ = new Collider(this);
}

void kwee::GameObject::deleteCollider()
{
	delete collider_;
	collider_ = 0;
}