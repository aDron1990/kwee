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
		~Camera(){};

	public:

		Camera(glm::vec4 viewport);

		glm::mat4 getViewProjectionMatrix();
		void useViewport();
	};
}