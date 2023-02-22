#pragma once

#include "kwee/core/api.h"
#include "Transformable.h"

#include <glm/glm.hpp>

namespace kwee
{
	class KWEEAPI Camera : public Transformable
	{
	private:

		glm::mat4 projection_;
		glm::vec4 viewport_;
		float aspect_;

	public:

		Camera(glm::vec4 viewport);
		~Camera() = default;

		void setVieport(glm::vec4 viewport);

		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();
		void useViewport();

		glm::vec2 ScreenToWorld(glm::fvec2 screenCoords);

	};
}