#include "systems/resource/resourceSystem.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace siofraEngine::systems
{
    ResourceSystem::ResourceSystem(std::unique_ptr<platform::IPlatformFileSystem> fileSystem, systems::IEventSystem & eventSystem) :
        fileSystem{std::move(fileSystem)},
        eventSystem{eventSystem}
    {
        loadShader("object_shader");
        loadMaterial("default_material");
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

    void ResourceSystem::loadMaterial(std::string materialName)
    {
        int width, height, channels, size;
		std::string fileLocation = assetBasePath + "materials\\" + materialName + ".png";

		stbi_uc * image = stbi_load(fileLocation.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		if (image)
		{
			size = width * height * 4;
		}

        std::vector<char> imageData(image, image + size);

        stbi_image_free(image);

        CreateMaterialEvent createMaterialEvent;
        createMaterialEvent.imageData = imageData;
        createMaterialEvent.width = width;
        createMaterialEvent.height = height;
        createMaterialEvent.channels = channels;
        eventSystem.broadcast(EventTypes::CREATE_MATERIAL, createMaterialEvent);
    }
}
