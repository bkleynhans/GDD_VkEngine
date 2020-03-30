#include "CommandBuffers.h"

CommandBuffers::CommandBuffers()
{

}

CommandBuffers::CommandBuffers(GpuProperties* pGpuProperties, Framebuffers* pFramebuffers)
{
    this->createCommandBuffers(pGpuProperties, pFramebuffers);
}

void CommandBuffers::createCommandBuffers(GpuProperties* pGpuProperties, Framebuffers* pFramebuffers)
{    
    this->pCommandBuffers = new std::vector<VkCommandBuffer>(pFramebuffers->pSwapChainFramebuffers->size());

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = *pCommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)this->pCommandBuffers->size();

    if (vkAllocateCommandBuffers(*pDevice, &allocInfo, this->pCommandBuffers->data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    for (size_t i = 0; i < this->pCommandBuffers->size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer((*this->pCommandBuffers)[i], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = *pRenderPass;
        renderPassInfo.framebuffer = (*pFramebuffers->pSwapChainFramebuffers)[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = pGpuProperties->pSwapChain->getSwapChainExtent();

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass((*this->pCommandBuffers)[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline((*this->pCommandBuffers)[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *pGraphicsPipeline);

        vkCmdDraw((*this->pCommandBuffers)[i], 3, 1, 0, 0);

        vkCmdEndRenderPass((*this->pCommandBuffers)[i]);

        if (vkEndCommandBuffer((*this->pCommandBuffers)[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}

CommandBuffers::~CommandBuffers()
{

}
