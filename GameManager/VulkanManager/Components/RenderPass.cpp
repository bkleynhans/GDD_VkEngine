#include "RenderPass.h"

RenderPass::RenderPass()
{

}

RenderPass::RenderPass(GpuProperties* pGpuProperties)
{
    this->createRenderPass(pGpuProperties);
}

void RenderPass::createRenderPass(GpuProperties* pGpuProperties)
{
// ATTACHMENT DESCRIPTION
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 117-119
        We’ll have a single color buffer attachment represented by one
        of the images from the swap chain.
    */
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = pGpuProperties->pSwapChain->getSwapChainImageFormat();
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
// END ATTACHMENT DESCRIPTION
// SUBPASSES AND ATTACHMENT REFERENCES
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 119
        A single render pass can consist of multiple subpasses. Subpasses are subsequent
        rendering operations that depend on the contents of framebuffers in previous
        passes, for example a sequence of post-processing effects that are applied one
        after another. If you group these rendering operations into one render pass,
        then Vulkan is able to reorder the operations and conserve memory bandwidth
        for possibly better performance. For our very first triangle, however, we’ll stick
        to a single subpass.
    */
    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
// END SUBPASSES AND ATTACHMENT REFERENCES
// RENDER PASS
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 120
        Now that the attachment and a basic subpass referencing it have been described,
        we can create the render pass itself. Create a new class member variable to hold
        the VkRenderPass object right above the pipelineLayout variable.
    */
    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
// END RENDER PASS

    pRenderPass = new VkRenderPass;

    if (vkCreateRenderPass(*pDevice, &renderPassInfo, nullptr, pRenderPass) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create render pass!");
    }
}

RenderPass::~RenderPass()
{
    // We created with the 'new' keyword so we need to clear memory
    delete pRenderPass;
}
