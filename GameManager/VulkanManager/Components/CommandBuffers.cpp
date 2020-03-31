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
    this->pBuffers = new std::vector<VkCommandBuffer>(pFramebuffers->pSwapChainFramebuffers->size());

// ALLOCATE COMMAND BUFFER
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 130
        Command buffers are allocated with the vkAllocateCommandBuffers function,
        which takes a VkCommandBufferAllocateInfo struct as parameter that specifies
        the command pool and number of buffers to allocate.

        The level parameter specifies if the allocated command buffers are primary or
        secondary command buffers.

            • VK_COMMAND_BUFFER_LEVEL_PRIMARY: Can be submitted to a queue for
                execution, but cannot be called from other command buffers.
            • VK_COMMAND_BUFFER_LEVEL_SECONDARY: Cannot be submitted directly,
                but can be called from primary command buffers.
    */
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = *pCommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)this->pBuffers->size();

    if (vkAllocateCommandBuffers(*pDevice, &allocInfo, this->pBuffers->data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }
// END ALLOCATE COMMAND BUFFER
// START COMMAND BUFFER RECORDING
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 131
        We begin recording a command buffer by calling vkBeginCommandBuffer with
        a small VkCommandBufferBeginInfo structure as argument that specifies some
        details about the usage of this specific command buffer.
    */
    for (size_t i = 0; i < this->pBuffers->size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer((*this->pBuffers)[i], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

// START OF RENDER PASS
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 132
        Drawing starts by beginning the render pass with vkCmdBeginRenderPass. The
        render pass is configured using some parameters in a VkRenderPassBeginInfo
        struct.
    */
        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = *pRenderPass;
        renderPassInfo.framebuffer = (*pFramebuffers->pSwapChainFramebuffers)[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = pGpuProperties->pSwapchain->getSwapChainExtent();

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass((*this->pBuffers)[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
// END RENDER PASS
// START BASIC DRAWING COMMANDS
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 133
        We can now bind the graphics pipeline.

        The second parameter specifies if the pipeline object is a graphics or compute
        pipeline. We’ve now told Vulkan which operations to execute in the graphics
        pipeline and which attachment to use in the fragment shader.
    */
        vkCmdBindPipeline((*this->pBuffers)[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *pGraphicsPipeline);

        vkCmdDraw((*this->pBuffers)[i], 3, 1, 0, 0);
// END BASIC DRAWING COMMANDS
// END THE RENDER PASS
        vkCmdEndRenderPass((*this->pBuffers)[i]);

        if (vkEndCommandBuffer((*this->pBuffers)[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
// END COMMAND BUFFER RECORDING
}

CommandBuffers::~CommandBuffers()
{

}
