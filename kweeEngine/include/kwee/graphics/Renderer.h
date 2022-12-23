#pragma once

#include "kwee/core/api.h"
#include "kwee/systems/ResourceManager.h"
#include "Shader.h"

#include <glad/glad.h>

namespace kwee
{
	class KWEEAPI Renderer
	{
	protected:

		GLuint vao_, vbo_, ebo_;
		Shader shader;

	public:

		virtual void draw(glm::mat4 MVP) = 0;
		virtual void updateBuffers(std::vector<float> vertices, std::vector<int> inddeices) = 0;

	};
}