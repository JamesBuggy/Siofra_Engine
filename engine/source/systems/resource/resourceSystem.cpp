#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include <algorithm>
#include <cstdint>
#include <stb/stb_image.h>
#include <tinyobjloader/tinyobjloader.h>
#include "systems/resource/resourceSystem.hpp"
#include "core/logging.hpp"
#include "core/ecs/components.hpp"
#include "math/math.hpp"
#include "utilities/constants.hpp"

namespace siofraEngine::systems
{
    ResourceSystem::ResourceSystem(std::unique_ptr<platform::IPlatformFileSystem> fileSystem, IEventSystem * const eventSystem) :
        fileSystem{std::move(fileSystem)},
        eventSystem{eventSystem}
    {
        loadShader("object_shader");
        loadMaterial(utilities::ResourceConstants::PlaceholderMaterialId);
        loadModel(utilities::ResourceConstants::PlaceholderModelId);
    }

    void ResourceSystem::loadShader(std::string const shaderName)
    {
        CreateShaderEvent createShaderEvent;
        createShaderEvent.vertexStageGlsl = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".vert.glsl");
        createShaderEvent.vertexStageSpirv = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".vert.spv");
        createShaderEvent.fragmentStageGlsl = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".frag.glsl");
        createShaderEvent.fragmentStageSpirv = fileSystem->readFile(assetBasePath + "shaders\\" + shaderName + ".frag.spv");
        eventSystem->broadcast(EventTypes::CREATE_SHADER, createShaderEvent);
    }

    void ResourceSystem::loadMaterial(std::string const materialName)
    {
        auto const configFile = assetBasePath + "materials\\" + materialName + ".matcfg";
        auto config = fileSystem->readConfigFile(configFile);

		int width, height, channels;
        auto const diffuseFile = assetBasePath + "materials\\" + config["diffuse"];
        stbi_uc * image = stbi_load(diffuseFile.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if (!image)
        {
            SE_LOG_WARNING("Failed to load material: " + diffuseFile);
            return;
        }

        int const size = width * height * 4;
        std::vector<char> const imageData(image, image + size);

        stbi_image_free(image);

        CreateMaterialEvent createMaterialEvent;
        createMaterialEvent.materialName = materialName;
        createMaterialEvent.diffuse.imageData = imageData;
        createMaterialEvent.diffuse.width = width;
        createMaterialEvent.diffuse.height = height;
        createMaterialEvent.diffuse.channels = channels;
        eventSystem->broadcast(EventTypes::CREATE_MATERIAL, createMaterialEvent);
    }

    void ResourceSystem::loadModel(std::string const modelName)
    {
        std::string modelDirectory = assetBasePath + "models\\";
        std::string fileLocation = modelDirectory + modelName + ".obj";

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warning;
        std::string error;

        bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, fileLocation.c_str(), modelDirectory.c_str());
        if (!result)
        {
            SE_LOG_WARNING("Failed to load model: " + fileLocation + ". Error: " + error);
            return;
        }

        std::vector<std::vector<std::uint32_t>> indexBuffers{ };
        std::vector<math::Vertex3> vertexBuffer(attrib.vertices.size()/3);
        for (auto const & shape : shapes)
        {
            tinyobj::mesh_t mesh = shape.mesh;
            std::vector<std::uint32_t> indices(mesh.indices.size());
            for (size_t j = 0; j < indices.size(); j++)
            {
                tinyobj::index_t index = mesh.indices[j];
                vertexBuffer[index.vertex_index].position = {
                    attrib.vertices[3 * static_cast<size_t>(index.vertex_index) + 0],
                    attrib.vertices[3 * static_cast<size_t>(index.vertex_index) + 1],
                    attrib.vertices[3 * static_cast<size_t>(index.vertex_index) + 2]
                };
                vertexBuffer[index.vertex_index].textureCoordinate = {
                    attrib.texcoords[2 * static_cast<size_t>(index.texcoord_index) + 0],
                    attrib.texcoords[2 * static_cast<size_t>(index.texcoord_index) + 1]
                };
                vertexBuffer[index.vertex_index].normal = { 
                    attrib.normals[3 * static_cast<size_t>(index.normal_index) + 0],
                    attrib.normals[3 * static_cast<size_t>(index.normal_index) + 1],
                    attrib.normals[3 * static_cast<size_t>(index.normal_index) + 2]
                };

                indices[j] = index.vertex_index;
            }

            indexBuffers.push_back(std::move(indices));
        }

        CreateModelEvent createModelEvent;
        createModelEvent.modelName = modelName;
        createModelEvent.vertexBuffer = std::move(vertexBuffer);
        createModelEvent.indexBuffers = std::move(indexBuffers);
        eventSystem->broadcast(EventTypes::CREATE_MODEL, createModelEvent);
    }

    void ResourceSystem::updateResources(core::Scene * scene)
    {
        auto const modelUpdates = scene->getEntities<core::ModelUpdated>();
        for (auto const & entity : modelUpdates)
        {
        	auto const modelComponent = scene->getComponent<core::Model>(entity);
            if (!loadedResources.contains(modelComponent->filename))
            {
                loadModel(modelComponent->filename);
                scene->removeComponent<core::ModelUpdated>(entity);
                loadedResources.insert(modelComponent->filename);
            }
        }

        auto const materialUpdates = scene->getEntities<core::MaterialUpdated>();
        for (auto const& entity : materialUpdates)
        {
            auto const materialComponent = scene->getComponent<core::Material>(entity);
            if (!loadedResources.contains(materialComponent->filename))
            {
                loadMaterial(materialComponent->filename);
                scene->removeComponent<core::MaterialUpdated>(entity);
                loadedResources.insert(materialComponent->filename);
            }
        }
    }
}
