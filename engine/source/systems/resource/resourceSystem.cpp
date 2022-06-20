#include "systems/resource/resourceSystem.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tinyobjloader.h"

namespace siofraEngine::systems
{
    ResourceSystem::ResourceSystem(std::unique_ptr<platform::IPlatformFileSystem> fileSystem, systems::IEventSystem * const eventSystem) :
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
        eventSystem->broadcast(EventTypes::CREATE_SHADER, createShaderEvent);
    }

    void ResourceSystem::loadMaterial(std::string materialName)
    {
        int width, height, channels, size;
        std::string fileLocation = assetBasePath + "materials\\" + materialName + ".png";

        stbi_uc * image = stbi_load(fileLocation.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if (!image)
        {
            throw std::runtime_error("Failed to load material: " + fileLocation);
        }

        size = width * height * 4;
        std::vector<char> imageData(image, image + size);

        stbi_image_free(image);

        CreateMaterialEvent createMaterialEvent;
        createMaterialEvent.materialName = materialName;
        createMaterialEvent.imageData = imageData;
        createMaterialEvent.width = width;
        createMaterialEvent.height = height;
        createMaterialEvent.channels = channels;
        eventSystem->broadcast(EventTypes::CREATE_MATERIAL, createMaterialEvent);
    }

    void ResourceSystem::loadModel(std::string modelName)
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
            SE_LOG_ERROR(error);
            throw std::runtime_error("Failed to load model: " + fileLocation);
        }

        std::vector<std::vector<std::uint32_t>> indexBuffers{ };
        std::vector<Vertex3> vertexBuffer(attrib.vertices.size());
        for (size_t i = 0; i < shapes.size(); i++)
        {
            tinyobj::mesh_t mesh = shapes[i].mesh;
            std::vector<std::uint32_t> indices(mesh.indices.size());
            for (size_t j = 0; j < indices.size(); j++)
            {
                tinyobj::index_t index = mesh.indices[j];
                vertexBuffer[index.vertex_index].position = {
                    attrib.vertices[3 * size_t(index.vertex_index) + 0],
                    attrib.vertices[3 * size_t(index.vertex_index) + 1],
                    attrib.vertices[3 * size_t(index.vertex_index) + 2]
                };
                vertexBuffer[index.vertex_index].textureCoordinate = {
                    attrib.texcoords[2 * size_t(index.texcoord_index) + 0],
                    attrib.texcoords[2 * size_t(index.texcoord_index) + 1]
                };
                vertexBuffer[index.vertex_index].normal = { 
                    attrib.normals[3 * size_t(index.normal_index) + 0],
                    attrib.normals[3 * size_t(index.normal_index) + 1],
                    attrib.normals[3 * size_t(index.normal_index) + 2]
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
        auto modelUpdates = scene->getEntities<core::ModelUpdated>();
        for (auto const & entity : modelUpdates)
        {
            auto modelComponent = scene->getComponent<core::Model>(entity);
            loadModel(modelComponent->filename);
            scene->removeComponent<core::ModelUpdated>(entity);
        }

        auto materialUpdates = scene->getEntities<core::MaterialUpdated>();
        for (auto const& entity : materialUpdates)
        {
            auto materialComponent = scene->getComponent<core::Material>(entity);
            loadMaterial(materialComponent->filename);
            scene->removeComponent<core::MaterialUpdated>(entity);
        }
    }
}
