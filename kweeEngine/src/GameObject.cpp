#include "kwee/game_primitives/GameObject.h"
#include "kwee/game_primitives/Scene.h"
#include "kwee/systems/ResourceManager.h"

kwee::GameObject::GameObject(Color color) : color(color)
{
	mesh_ = ResourceManager::getMesh();
	shader_ = ResourceManager::getShader("colored");
	textured_ = false;
}

kwee::GameObject::GameObject(std::string textureName)
{
	mesh_ = ResourceManager::getMesh();
	shader_ = ResourceManager::getShader("textured");
	texture_ = ResourceManager::getTexture(textureName);
	textured_ = true;
}

kwee::GameObject::~GameObject()
{
	owner_->removeObject(this);
	deleteCollider();
}

void kwee::GameObject::setOwnerScene(Scene* owner)
{
	owner_ = owner;
}

kwee::Scene* kwee::GameObject::getOwnerScene()
{
	return owner_;
}

void kwee::GameObject::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (textured_) texture_->bind();
	shader_->use();
	shader_->setUniformVector3("color", glm::vec3(color.red, color.green, color.blue));
	shader_->setUniformFloat("mixval", mix);
	shader_->setUniformMatrix4("model", getTransformMatrix());
	shader_->setUniformMatrix4("view", viewMatrix);
	shader_->setUniformMatrix4("projection", projectionMatrix);
	mesh_->draw();
	if (collider_ != 0 && colliderIsDrawing)
	{
		auto shader = ResourceManager::getShader("collider");
		shader->use();
		shader_->setUniformMatrix4("model", getTransformMatrix());
		shader_->setUniformMatrix4("view", viewMatrix);
		shader_->setUniformMatrix4("projection", projectionMatrix);
		collider_->draw();
	}
}

void kwee::GameObject::createCollider(bool collisionSupport, bool mouseSupport)
{
	if (collider_ == 0) collider_ = new Collider(this, collisionSupport, mouseSupport);
}

void kwee::GameObject::deleteCollider()
{
	delete collider_;
	collider_ = 0;
}