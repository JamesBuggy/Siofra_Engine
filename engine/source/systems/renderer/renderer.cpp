#include "systems/renderer/renderer.hpp"

namespace siofraEngine::systems
{
    Renderer::Renderer(RendererImpls rendererImpl) :
        rendererBackend{createRendererBackend(rendererImpl)}
    {

    }

    std::unique_ptr<IRendererImpl> Renderer::createRendererBackend(RendererImpls rendererImpl)
    {
        std::unique_ptr<IRendererImpl> rendererBackend(nullptr);

        switch (rendererImpl)
        {
        case RendererImpls::Vulkan :
            rendererBackend = std::make_unique<VulkanRenderer>();
            break;
        }

        SE_ASSERT_TRUE(rendererBackend != nullptr, "Unsupported renderer implementation");
        return rendererBackend;
    }
}