#ifndef _COMMANDBUFFERS_H_
#define _COMMANDBUFFERS_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/Framebuffers.h"
#include "VulkanManager/Components/GpuProperties.h"

class CommandBuffers :
    public ComponentsBase
{
public:
    CommandBuffers();    
    CommandBuffers(GpuProperties* pGpuProperties, Framebuffers* pFramebuffers);
    ~CommandBuffers();

    void createCommandBuffers(GpuProperties* pGpuProperties, Framebuffers* pFramebuffers);

    std::vector<VkCommandBuffer>*pCommandBuffers;
};

#endif // _COMMANDBUFFERS_H_