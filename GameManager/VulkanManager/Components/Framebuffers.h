#ifndef _FRAMEBUFFERS_H_
#define _FRAMEBUFFERS_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/GpuProperties.h"

// Framebuffer Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 125
    The attachments specified during render pass creation are bound by wrapping
    them into a VkFramebuffer object. A framebuffer object references all of the
    VkImageView objects that represent the attachments. In our case that will be
    only a single one: the color attachment. However, the image that we have to
    use for the attachment depends on which image the swap chain returns when we
    retrieve one for presentation. That means that we have to create a framebuffer
    for all of the images in the swap chain and use the one that corresponds to the
    retrieved image at drawing time.
*/

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