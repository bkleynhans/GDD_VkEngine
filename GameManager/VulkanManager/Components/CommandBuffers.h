#ifndef _COMMANDBUFFERS_H_
#define _COMMANDBUFFERS_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/Framebuffers.h"
#include "VulkanManager/Components/GpuProperties.h"

// Command Buffer Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 130
    We can now start allocating command buffers and recording drawing commands
    in them. Because one of the drawing commands involves binding the right
    VkFramebuffer, we’ll actually have to record a command buffer for every image
    in the swap chain once again.
*/
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