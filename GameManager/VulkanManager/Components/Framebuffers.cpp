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
        framebufferInfo.width = pGpuProperties->pSwapChain->getSwapChainExtent().width;
        framebufferInfo.height = pGpuProperties->pSwapChain->getSwapChainExtent().height;
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
