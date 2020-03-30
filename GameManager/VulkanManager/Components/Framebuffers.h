#ifndef _FRAMEBUFFERS_H_
#define _FRAMEBUFFERS_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/GpuProperties.h"

class Framebuffers :
    public ComponentsBase
{
public:
    Framebuffers();
    Framebuffers(GpuProperties* pGpuProperties, std::vector<VkImageView>* pSwapChainImageViews);
    ~Framebuffers();

    void createFramebuffers(GpuProperties* pGpuProperties, std::vector<VkImageView>* pSwapChainImageViews);

    std::vector<VkFramebuffer>* pSwapChainFramebuffers = nullptr;
};

#endif _FRAMEBUFFERS_H_