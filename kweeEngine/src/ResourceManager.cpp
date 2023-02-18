#include "kwee/systems/ResourceManager.h"
#include "res/standart_shaders.res.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::pair<std::string, std::shared_ptr<kwee::Shader>>> kwee::ResourceManager::shaders_ = std::vector<std::pair<std::string, std::shared_ptr<kwee::Shader>>>();
std::shared_ptr<kwee::Mesh> kwee::ResourceManager::mesh_ = nullptr;

void kwee::ResourceManager::initialize()
{
    mesh_ = std::make_shared<Mesh>();
    shaders_.push_back(std::pair<std::string, std::shared_ptr<Shader>>("colored", compileShader_(colored_v_str, colored_f_str)));
    shaders_.push_back(std::pair<std::string, std::shared_ptr<Shader>>("collider", compileShader_(collider_v_str, collider_f_str)));
}

void kwee::ResourceManager::terminate()
{
    for (int i = 0; i < shaders_.size(); i++)
    {
        shaders_[i].second.~shared_ptr();
    }
    mesh_.~shared_ptr();
}

void kwee::ResourceManager::loadShader(const std::string vertexShaderFilePath, const std::string fragmentShaderFilePath, const std::string resourceName)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexShaderFilePath);
        fShaderFile.open(fragmentShaderFilePath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        shaders_.push_back(std::pair<std::string, std::shared_ptr<Shader>>(resourceName, std::make_shared<Shader>(vertexCode, fragmentCode)));
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
}

std::shared_ptr<kwee::Shader> kwee::ResourceManager::compileShader_(const std::string vertexShaderCode, const std::string fragmentShaderCode)
{
    return std::make_shared<Shader>(vertexShaderCode, fragmentShaderCode);
}

std::shared_ptr<kwee::Shader> kwee::ResourceManager::getShader(const std::string resourceName)
{
    for (int i = 0; i < shaders_.size(); i++)
    {
        if (shaders_[i].first == resourceName) return shaders_[i].second;
    }

    throw;
}

std::shared_ptr<kwee::Mesh> kwee::ResourceManager::getMesh()
{
    return mesh_;
}