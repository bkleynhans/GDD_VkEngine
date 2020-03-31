#include "GameManager.h"

GameManager::GameManager()
{

}

void GameManager::run()
{    
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void GameManager::initWindow()
{
    this->pWindowManager = new WindowManager();
}

void GameManager::initVulkan()
{
    this->pVulkanManager = new VulkanManager(this->pWindowManager);
}

void GameManager::mainLoop()
{
    while (!glfwWindowShouldClose(this->pWindowManager->pWindow))
    {
        glfwPollEvents();
        drawFrame();
    }
}

void GameManager::drawFrame()
{
    vkWaitForFences(
        this->pVulkanManager->getDevice(),
        1,
        &(*this->pVulkanManager->pInFlightFences)[this->pVulkanManager->currentFrame],
        VK_TRUE,
        UINT64_MAX
    );

    uint32_t imageIndex;
    vkAcquireNextImageKHR(
        this->pVulkanManager->getDevice(),
        this->pVulkanManager->getSwapchain(),
        UINT64_MAX,
        (*this->pVulkanManager->pImageAvailableSemaphores)[this->pVulkanManager->currentFrame],
        VK_NULL_HANDLE,
        &imageIndex
    );

    if ((*this->pVulkanManager->pImagesInFlight)[imageIndex] != VK_NULL_HANDLE)
    {
        vkWaitForFences(
            this->pVulkanManager->getDevice(),
            1, 
            &(*this->pVulkanManager->pImagesInFlight)[imageIndex],
            VK_TRUE,
            UINT64_MAX
        );
    }
    (*this->pVulkanManager->pImagesInFlight)[imageIndex] = (*this->pVulkanManager->pInFlightFences)[this->pVulkanManager->currentFrame];

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { (*this->pVulkanManager->pImageAvailableSemaphores)[this->pVulkanManager->currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = this->pVulkanManager->getPCommandBuffers(imageIndex);

    VkSemaphore signalSemaphores[] = { (*this->pVulkanManager->pRenderFinishedSemaphores)[this->pVulkanManager->currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(
        this->pVulkanManager->getDevice(),
        1,
        &(*this->pVulkanManager->pInFlightFences)[this->pVulkanManager->currentFrame]
    );
    
    if (vkQueueSubmit(
        this->pVulkanManager->getGraphicsQueue(),
        1,
        &submitInfo,
        (*this->pVulkanManager->pInFlightFences)[this->pVulkanManager->currentFrame]) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { this->pVulkanManager->getSwapchain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(this->pVulkanManager->getPresentQueue(), &presentInfo);

    this->pVulkanManager->currentFrame = (this->pVulkanManager->currentFrame + 1) % this->pVulkanManager->MAX_FRAMES_IN_FLIGHT;
}

void GameManager::cleanup()
{

}

GameManager::~GameManager()
{
    delete this->pVulkanManager;
    delete this->pWindowManager;
}