#include "ComponentsBase.h"

WindowManager* ComponentsBase::pWindowManager = nullptr;
EntityManager* ComponentsBase::pEntityManager = nullptr;
BodyManager* ComponentsBase::pBodyManager = nullptr;

VkInstance* ComponentsBase::pInstance = nullptr;
VkSurfaceKHR* ComponentsBase::pSurface = nullptr;
VkQueue* ComponentsBase::pGraphicsQueue = nullptr;
VkQueue* ComponentsBase::pPresentQueue = nullptr;
VkSwapchainKHR* ComponentsBase::pSwapchain = nullptr;
VkRenderPass* ComponentsBase::pRenderPass = nullptr;
VkPipelineLayout* ComponentsBase::pPipelineLayout = nullptr;
VkPipeline* ComponentsBase::pGraphicsPipeline = nullptr;
VkBuffer* ComponentsBase::pVBuffer = nullptr;
VkDeviceMemory* ComponentsBase::pVBufferMemory = nullptr;
VkCommandPool* ComponentsBase::pCommandPool = nullptr;
VkBuffer* ComponentsBase::pIndexBuffer = nullptr;
VkDeviceMemory* ComponentsBase::pIndexBufferMemory = nullptr;

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

void ComponentsBase::setPWindowManager(WindowManager* pWindow)
{
    pWindowManager = pWindow;
}

GLFWwindow* ComponentsBase::getPWindow()
{
    return pWindowManager->pWindow;
}

void ComponentsBase::setPEntityManager(EntityManager* pEntity)
{
    pEntityManager = pEntity;
    pBodyManager = pEntityManager->getPBodyManager();
}

ComponentsBase::~ComponentsBase()
{

}