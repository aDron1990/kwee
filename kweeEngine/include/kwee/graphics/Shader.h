#pragma once

#include "kwee/core/api.h"

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace kwee
{
	class KWEEAPI Shader
	{
		friend class ResourceManager;

	private:

		GLuint id_;

		void free();

	public:

		Shader(){};
		Shader(std::string vertexShaderCode, std::string fragmentShaderCode);

		void use();
		void setUniformMatrix4(std::string uniformName, glm::mat4 matrix);

	};
}