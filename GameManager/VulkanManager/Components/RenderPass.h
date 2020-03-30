#ifndef _RENDERPASS_H_
#define _RENDERPASS_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/GpuProperties.h"

// Render Passes
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 117
    Before we can finish creating the pipeline, we need to tell Vulkan about the
    framebuffer attachments that will be used while rendering. We need to specify
    how many color and depth buffers there will be, how many samples to use
    for each of them and how their contents should be handled throughout the
    rendering operations. All of this information is wrapped in a render pass object.
*/

class RenderPass :
    public ComponentsBase
{
public:
    RenderPass();
    RenderPass(GpuProperties* pGpuProperties);
    ~RenderPass();

    void createRenderPass(GpuProperties* pGpuProperties);
};

#endif // _RENDERPASS_H_