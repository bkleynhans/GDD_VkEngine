#include "Framebuffers.h"

Framebuffers::Framebuffers()
{
    
}

Framebuffers::Framebuffers(GpuProperties* pGpuProperties, std::vector<VkImageView>* pSwapChainImageViews)
{
    this->createFramebuffers(pGpuProperties, pSwapChainImageViews);
}

void Framebuffers::createFramebuffers(GpuProperties* pGpuProperties, std::vector<VkImageView>* pSwapChainImageViews)
{
    this->pSwapChainFramebuffers = new std::vector<VkFramebuffer>(pSwapChainImageViews->size());

    // Iterate through the image views and create frame buffers for each of them
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 126
        Creation of framebuffers is quite straightforward. We first need
        to specify with which renderPass the framebuffer needs to be compatible. You
        can only use a framebuffer with the render passes that it is compatible with,
        which roughly means that they use the same number and type of attachments.
        
        The attachmentCount and pAttachments parameters specify the VkImageView
        objects that should be bound to the respective attachment descriptions in the
        render pass pAttachment array.
        
        The width and height parameters are self-explanatory and layers refers to
        the number of layers in image arrays. Our swap chain images are single images,
        so the number of layers is 1.
    */
    for (size_t i = 0; i < pSwapChainImageViews->size(); i++)
    {
        VkImageView attachments[] = {
            (*pSwapChainImageViews)[i]
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = *pRenderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = pGpuProperties->pSwapchain->getSwapChainExtent().width;
        framebufferInfo.height = pGpuProperties->pSwapchain->getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(*pDevice, &framebufferInfo, nullptr, &(*this->pSwapChainFramebuffers)[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

Framebuffers::~Framebuffers()
{

}
