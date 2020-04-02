#include "ComponentsBase.h"

WindowManager* ComponentsBase::pWindowManager = nullptr;

VkInstance* ComponentsBase::pInstance = nullptr;
VkSurfaceKHR* ComponentsBase::pSurface = nullptr;
VkQueue* ComponentsBase::pGraphicsQueue = nullptr;
VkQueue* ComponentsBase::pPresentQueue = nullptr;
VkSwapchainKHR* ComponentsBase::pSwapchain = nullptr;
VkRenderPass* ComponentsBase::pRenderPass = nullptr;
VkPipelineLayout* ComponentsBase::pPipelineLayout = nullptr;
VkPipeline* ComponentsBase::pGraphicsPipeline = nullptr;
VkCommandPool* ComponentsBase::pCommandPool = nullptr;

VkDevice* ComponentsBase::pDevice = nullptr;
VkPhysicalDevice* ComponentsBase::pPhysicalDevice = VK_NULL_HANDLE;

ComponentsBase::ComponentsBase()
{

}

VkDevice ComponentsBase::getDevice()
{
    return *pDevice;
}

VkInstance ComponentsBase::getInstance()
{
    return *pInstance;
}

VkSwapchainKHR ComponentsBase::getSwapchain()
{
    return *pSwapchain;
}

VkPhysicalDevice ComponentsBase::getPhysicalDevice()
{
    return *pPhysicalDevice;
}

VkQueue ComponentsBase::getGraphicsQueue()
{
    return *pGraphicsQueue;
}

VkQueue ComponentsBase::getPresentQueue()
{
    return *pPresentQueue;
}

ComponentsBase::~ComponentsBase()
{

}