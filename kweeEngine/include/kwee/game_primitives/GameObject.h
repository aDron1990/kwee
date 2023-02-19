#pragma once

#include "kwee/core/api.h"
#include "Transformable.h"
#include "kwee/graphics/Mesh.h"
#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Texture.h"
#include "kwee/graphics/Color.h"
#include "Collider.h"

#include <string>
#include <glm/glm.hpp>
#include <kwee/graphics/Shader.h>
#include <memory>

namespace kwee
{
	class KWEEAPI Scene;
	class KWEEAPI GameObject : public Transformable
	{
	private:

		std::shared_ptr<Shader> shader_;
		std::shared_ptr<Texture> texture_;
		std::shared_ptr<Mesh> mesh_;
		Color color_;
		Scene* owner_;
		Collider* collider_ = 0;
		bool textured_;

	protected:

		virtual ~GameObject();

	public:

		bool colliderIsDrawing = false;

		void createCollider(bool collisionSupport, bool mouseSupport);
		void deleteCollider();

		virtual void onCollision(Collider* other) {};
		virtual void onCollisionEnter(Collider* other) {};
		virtual void onCollisionExit(Collider* other) {};

		virtual void onMouseHover() {};
		virtual void onMouseHoverEnter() {};
		virtual void onMouseHoverExit() {};

		GameObject(kwee::Color color);
		GameObject(std::string textureName);

		void setOwnerScene(Scene* owner);
		Scene* getOwnerScene();
//		Mesh getMesh();

		void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
		virtual void update() {};
	};
}