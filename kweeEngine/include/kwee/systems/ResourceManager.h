#pragma once

#include "kwee/core/api.h"
#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Mesh.h"

#include <vector>
#include <string>
#include <memory>

namespace kwee
{
	class KWEEAPI ResourceManager
	{
	private:

		static std::vector<std::pair<std::string, std::shared_ptr<Shader>>> shaders_;
		static std::shared_ptr<Mesh> mesh_;

		static std::shared_ptr<Shader> compileShader_(const std::string vertexShaderCode, const std::string fragmentShaderCode);

	public:

		static void initialize();
		static void terminate();

		static void loadShader(const std::string vertexShaderFilePath, const std::string fragmentShaderFilePath, const std::string resourceName);

		static std::shared_ptr<Shader> getShader(const std::string resourceName);
		static std::shared_ptr<Mesh> getMesh();

	};
}