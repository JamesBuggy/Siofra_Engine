#pragma once

#include <vector>
#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanBuffer.hpp"

namespace siofraEngine::systems
{
    struct Model
    {
        std::unique_ptr<IVulkanBuffer> vertexBuffer;
        std::vector<std::unique_ptr<IVulkanBuffer>> indexBuffers;
    };
}
