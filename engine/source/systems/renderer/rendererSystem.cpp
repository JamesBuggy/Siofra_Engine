#include "systems/renderer/rendererSystem.hpp"

namespace siofraEngine::systems
{
    RendererSystem::RendererSystem(siofraEngine::platform::IWindow &window, systems::IEventSystem * const eventSystem) :
        rendererBackend{createRendererBackend(window)}
    {
        eventSystem->subscribe(EventTypes::CREATE_SHADER, std::bind(&RendererSystem::createShader, this, std::placeholders::_1));
        eventSystem->subscribe(EventTypes::CREATE_MATERIAL, std::bind(&RendererSystem::createMaterial, this, std::placeholders::_1));
        eventSystem->subscribe(EventTypes::CREATE_MODEL, std::bind(&RendererSystem::createModel, this, std::placeholders::_1));

        viewProjection.projection = math::Matrix4x4::perspective(math::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 400.0f);
        viewProjection.projection.elements[5] *= -1;
        viewProjection.view = math::Matrix4x4::lookAt(math::Vector3(0.0f, 1.0f, 0.0f), math::Vector3(0.0f, 1.0f, 0.0f) + math::Vector3(0.0f, 0.0f, 1.0f), math::Vector3(0.0f, 1.0f, 0.0f));

        SE_LOG_INFO("Initialized renderer system");
    }

    void RendererSystem::draw(core::Scene* scene)
    {
        rendererBackend->beginFrame();

        auto cameras = scene->getEntities<core::Camera, core::Transform>();
        if (cameras.size())
        {
            auto camera = cameras.front();
            auto cameraComponent = scene->getComponent<core::Camera>(camera);
            auto transformComponent = scene->getComponent<core::Transform>(camera);

            viewProjection.view = math::Matrix4x4::lookAt(transformComponent->position, transformComponent->position + cameraComponent->front, math::Vector3(0.0f, 1.0f, 0.0f));
            rendererBackend->setViewProjection(viewProjection);
        }

        auto entities = scene->getEntities<core::Model, core::Transform, core::Rotation>();
        for (auto const & entity : entities)
        {
            auto modelComponent = scene->getComponent<core::Model>(entity);
            auto materialComponent = scene->getComponent<core::Material>(entity);
            auto transformComponent = scene->getComponent<core::Transform>(entity);
            auto rotationComponent = scene->getComponent<core::Rotation>(entity);

            std::string material{ materialComponent ? materialComponent->filename : "" };
            std::string model{ modelComponent ? modelComponent->filename : "" };
            
            math::Matrix4x4 modelMatrix = math::Matrix4x4::translation(transformComponent->position);
            modelMatrix = modelMatrix * math::Matrix4x4::rotationY(math::radians(rotationComponent->angle));

            rendererBackend->draw(material, model, modelMatrix);
        }

        rendererBackend->endFrame();
    }

    std::unique_ptr<IRendererBackend> RendererSystem::createRendererBackend(siofraEngine::platform::IWindow &window)
    {
        std::unique_ptr<IRendererBackend> rendererBackend(nullptr);
        siofraEngine::platform::WindowFlags windowFlags = window.getFlags();

        if((windowFlags & siofraEngine::platform::WindowFlags::WINDOW_VULKAN) == siofraEngine::platform::WindowFlags::WINDOW_VULKAN)
        {
            rendererBackend = std::make_unique<VulkanRenderer>(window);
        }

        SE_ASSERT_TRUE(rendererBackend != nullptr, "Unsupported renderer implementation");
        return rendererBackend;
    }

    void RendererSystem::createShader(EventPayload payload)
    {
        auto shaderData = std::get<CreateShaderEvent>(payload);
        switch (rendererBackend->getRendererBackendType())
        {
        case RendererBackends::VULKAN :
            rendererBackend->createShader(shaderData.vertexStageSpirv, shaderData.fragmentStageSpirv);
            break;

        default:
            SE_LOG_CRITICAL("Create shader: Failed to identify renderer backend");
        }
    }

    void RendererSystem::createMaterial(EventPayload payload)
    {
        auto createMaterialEvent = std::get<CreateMaterialEvent>(payload);
        rendererBackend->createMaterial(
            createMaterialEvent.materialName,
            createMaterialEvent.imageData,
            createMaterialEvent.width,
            createMaterialEvent.height,
            createMaterialEvent.channels);
    }

    void RendererSystem::createModel(EventPayload payload)
    {
        auto createModelEvent = std::get<CreateModelEvent>(payload);
        rendererBackend->createModel(createModelEvent.modelName, std::move(createModelEvent.vertexBuffer), std::move(createModelEvent.indexBuffers));
    }
}
