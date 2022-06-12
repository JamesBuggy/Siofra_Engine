#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanShaderModuleBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanShaderModuleBuilder& VulkanShaderModule::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanShaderModuleBuilder& VulkanShaderModule::Builder::withShaderCode(std::vector<char> shaderCode) noexcept
    {
        this->shaderCode = shaderCode;
        return *this;
    }

    std::unique_ptr<IVulkanShaderModule> VulkanShaderModule::Builder::build() const
    {
        VkShaderModuleCreateInfo shaderModuleCreateInfo{ };
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());
		shaderModuleCreateInfo.codeSize = shaderCode.size();

		VkShaderModule shaderModule{ VK_NULL_HANDLE };
		if (vkCreateShaderModule(device->getLogicalDevice(), &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a shader module");
		}

        return std::make_unique<VulkanShaderModule>(shaderModule, device);
    }
}
