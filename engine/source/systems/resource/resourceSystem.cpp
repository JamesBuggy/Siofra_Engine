#include "systems/resource/resourceSystem.hpp"

namespace siofraEngine::systems
{
    ResourceSystem::ResourceSystem(std::unique_ptr<platform::IPlatformFileSystem> fileSystem, systems::IEventSystem & eventSystem) :
        fileSystem{std::move(fileSystem)},
        eventSystem{eventSystem}
    {
        loadShader("object_shader");
    }

    void ResourceSystem::loadShader(std::string shaderName)
    {
        CreateShaderEvent createShaderEvent;
        createShaderEvent.vertexStageGlsl = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".vert.glsl");
        createShaderEvent.vertexStageSpirv = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".vert.spv");
        createShaderEvent.fragmentStageGlsl = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".frag.glsl");
        createShaderEvent.fragmentStageSpirv = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".frag.spv");
        eventSystem.broadcast(EventTypes::CREATE_SHADER, createShaderEvent);
    }
}
