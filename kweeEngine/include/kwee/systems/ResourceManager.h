#pragma once

#include "kwee/core/api.h"
#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Mesh.h"

#include <vector>
#include <string>

namespace kwee
{
	class KWEEAPI ResourceManager
	{
	private:

		static std::vector<std::pair<std::string, Shader*>> shaders_;
		static std::vector<std::pair<std::string, Mesh*>> meshes_;

	public:

		static void initialize();
		static void terminate();

		static void loadShader(const std::string vertexShaderFilePath, const std::string fragmentShaderFilePath, const std::string resourceName);
		static Shader getShader(const std::string resourceName);

		static Mesh getMesh(const std::string resourceName);

	};
}