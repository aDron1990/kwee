#include "kwee/systems/ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::pair<std::string, kwee::Shader*>> kwee::ResourceManager::shaders_ = std::vector<std::pair<std::string, kwee::Shader*>>();
std::vector<std::pair<std::string, kwee::Mesh*>> kwee::ResourceManager::meshes_ = std::vector<std::pair<std::string, kwee::Mesh*>>();

void kwee::ResourceManager::initialize()
{
    meshes_.push_back(std::pair<std::string, Mesh*>("rectangle", new Mesh));
}

void kwee::ResourceManager::terminate()
{
    for (int i = 0; i < shaders_.size(); i++)
    {
        shaders_[i].second->free();
        delete shaders_[i].second;
    }
    for (int i = 0; i < meshes_.size(); i++)
    {
        meshes_[i].second->free();
        delete meshes_[i].second;
    }
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

        shaders_.push_back(std::pair<std::string, Shader*>(resourceName, new Shader(vertexCode, fragmentCode)));
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
}

kwee::Shader kwee::ResourceManager::getShader(const std::string resourceName)
{
    for (int i = 0; i < shaders_.size(); i++)
    {
        if (shaders_[i].first == resourceName) return *shaders_[i].second;
    }

    throw;
}

kwee::Mesh kwee::ResourceManager::getMesh(const std::string resourceName)
{
    return *meshes_[0].second;
}