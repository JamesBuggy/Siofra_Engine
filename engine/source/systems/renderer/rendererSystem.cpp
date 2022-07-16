#include <string>
#include "systems/renderer/rendererSystem.hpp"
#include "systems/renderer/vulkan/vulkanRenderer.hpp"
#include "core/ecs/components.hpp"
#include "math/math.hpp"
#include "core/logging.hpp"
#include "core/assertions.hpp"

namespace siofraEngine::systems
{
    RendererSystem::RendererSystem(platform::IWindow &window, IEventSystem * const eventSystem) :
        rendererBackend{createRendererBackend(window)}
    {
        eventSystem->subscribe(EventTypes::CREATE_SHADER, [this](EventPayload && payload) { createShader(payload); });
        eventSystem->subscribe(EventTypes::CREATE_MATERIAL, [this](EventPayload && payload) { createMaterial(payload); });
        eventSystem->subscribe(EventTypes::CREATE_MODEL, [this](EventPayload && payload) { createModel(payload); });

        viewProjection.projection = math::Matrix4x4::perspective(math::radians(45.0f), static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()), 0.1f, 400.0f);
        viewProjection.projection.elements[5] *= -1;
        viewProjection.view = math::Matrix4x4::lookAt(math::Vector3(0.0f, 1.0f, 0.0f), math::Vector3(0.0f, 1.0f, 0.0f) + math::Vector3(0.0f, 0.0f, 1.0f), math::Vector3(0.0f, 1.0f, 0.0f));

        SE_LOG_INFO("Initialized renderer system");
    }

    void RendererSystem::draw(core::Scene* scene)
    {
        rendererBackend->beginFrame();

        auto const cameras = scene->getEntities<core::Camera, core::Transform>();
        if (!cameras.empty())
        {
            auto const camera = cameras.front();
            auto const cameraComponent = scene->getComponent<core::Camera>(camera);
            auto const transformComponent = scene->getComponent<core::Transform>(camera);

            viewProjection.view = math::Matrix4x4::lookAt(transformComponent->position, transformComponent->position + cameraComponent->front, math::Vector3(0.0f, 1.0f, 0.0f));
            rendererBackend->setViewProjection(viewProjection);
        }

        auto const entities = scene->getEntities<core::Model, core::Transform, core::Rotation>();
        for (auto const & entity : entities)
        {
            auto const modelComponent = scene->getComponent<core::Model>(entity);
            auto const materialComponent = scene->getComponent<core::Material>(entity);
            auto const transformComponent = scene->getComponent<core::Transform>(entity);
            auto const rotationComponent = scene->getComponent<core::Rotation>(entity);

            std::string const material{ materialComponent ? materialComponent->filename : "" };
            std::string const model{ modelComponent ? modelComponent->filename : "" };
            
            math::Matrix4x4 modelMatrix = math::Matrix4x4::translation(transformComponent->position);
            modelMatrix = modelMatrix * math::Matrix4x4::rotationX(math::radians(rotationComponent->angles.x));
            modelMatrix = modelMatrix * math::Matrix4x4::rotationY(math::radians(rotationComponent->angles.y));
            modelMatrix = modelMatrix * math::Matrix4x4::rotationZ(math::radians(rotationComponent->angles.z));

            rendererBackend->draw(material, model, modelMatrix);
        }

        rendererBackend->endFrame();
    }

    std::unique_ptr<IRendererBackend> RendererSystem::createRendererBackend(platform::IWindow &window)
    {
        std::unique_ptr<IRendererBackend> rendererBackend(nullptr);
        platform::WindowFlags const windowFlags = window.getFlags();

        if((windowFlags & platform::WindowFlags::WINDOW_VULKAN) == platform::WindowFlags::WINDOW_VULKAN)
        {
            rendererBackend = std::make_unique<VulkanRenderer>(window);
        }

        SE_ASSERT_TRUE(rendererBackend != nullptr, "Unsupported renderer implementation");
        return rendererBackend;
    }

    void RendererSystem::createShader(EventPayload payload) const
    {
        auto const shaderData = std::get<CreateShaderEvent>(payload);
        switch (rendererBackend->getRendererBackendType())
        {
        case RendererBackends::VULKAN :
            rendererBackend->createShader(shaderData.vertexStageSpirv, shaderData.fragmentStageSpirv);
            break;

        default:
            SE_LOG_CRITICAL("Create shader: Failed to identify renderer backend");
        }
    }

    void RendererSystem::createMaterial(EventPayload payload) const
    {
        auto const & createMaterialEvent = std::get<CreateMaterialEvent>(payload);
        rendererBackend->createMaterial(
            createMaterialEvent.materialName,
            createMaterialEvent.diffuse.imageData,
            createMaterialEvent.diffuse.width,
            createMaterialEvent.diffuse.height,
            createMaterialEvent.diffuse.channels);
    }

    void RendererSystem::createModel(EventPayload payload) const
    {
        auto createModelEvent = std::get<CreateModelEvent>(payload);
        rendererBackend->createModel(createModelEvent.modelName, std::move(createModelEvent.vertexBuffer), std::move(createModelEvent.indexBuffers));
    }
}
