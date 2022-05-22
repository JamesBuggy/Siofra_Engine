#pragma once

#include <memory>
#include "core/assertions.hpp"
#include "systems/renderer/irendererImpl.hpp"
#include "systems/renderer/vulkan/vulkanRenderer.hpp"

namespace siofraEngine::systems
{
    enum class RendererImpls
    {
        Vulkan
    };

    class Renderer
    {
    public:
        Renderer(RendererImpls rendererImpl);

    private:
        std::unique_ptr<IRendererImpl> rendererBackend{ };

        static std::unique_ptr<IRendererImpl> createRendererBackend(RendererImpls rendererImpl);
    };
}
