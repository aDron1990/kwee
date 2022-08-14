#pragma once

#include "kwee/core/api.h"
#include "Transformable.h"
#include "kwee/graphics/Mesh.h"
#include "kwee/graphics/Shader.h"
#include "Collider.h"

#include <string>
#include <glm/glm.hpp>
#include <kwee/graphics/Shader.h>

namespace kwee
{
	class KWEEAPI Scene;
	class KWEEAPI GameObject : public Transformable
	{
	private:

		Shader shader_;
		Mesh mesh_;
		Scene* owner_;
		Collider* collider_;

	protected:

		virtual ~GameObject() {};

	public:

		bool colliderIsDrawing = false;

		void createCollider();
		void deleteCollider();

		virtual void onCollision(Collider* other) {};
		virtual void onCollisionEnter(Collider* other) {};
		virtual void onCollisionExit(Collider* other) {};

		GameObject(std::string meshResourñeName, std::string shaderResourñeName);
		void destroy();

		void setOwnerScene(Scene* owner);
		Mesh getMesh();

		void draw(glm::mat4 viewProjectionMatrix);
		virtual void update(){};
	};
}