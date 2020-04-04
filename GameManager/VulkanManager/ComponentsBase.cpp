#include "ComponentsBase.h"

WindowManager* ComponentsBase::pWindowManager = nullptr;
EntityManager* ComponentsBase::pEntityManager = nullptr;
BodyManager* ComponentsBase::pBodyManager = nullptr;

VkInstance* ComponentsBase::pInstance = nullptr;
VkSurfaceKHR* ComponentsBase::pSurface = nullptr;

VkPhysicalDevice* ComponentsBase::pPhysicalDevice = VK_NULL_HANDLE;
VkDevice* ComponentsBase::pDevice = nullptr;

VkQueue* ComponentsBase::pGraphicsQueue = nullptr;
VkQueue* ComponentsBase::pPresentQueue = nullptr;

VkSwapchainKHR* ComponentsBase::pSwapchain = nullptr;

VkRenderPass* ComponentsBase::pRenderPass = nullptr;
VkDescriptorSetLayout* ComponentsBase::pDescriptorSetLayout = nullptr;
VkPipelineLayout* ComponentsBase::pPipelineLayout = nullptr;
VkPipeline* ComponentsBase::pGraphicsPipeline = nullptr;

VkCommandPool* ComponentsBase::pCommandPool = nullptr;

VkBuffer* ComponentsBase::pVBuffer = nullptr;
VkDeviceMemory* ComponentsBase::pVBufferMemory = nullptr;
VkBuffer* ComponentsBase::pIndexBuffer = nullptr;
VkDeviceMemory* ComponentsBase::pIndexBufferMemory = nullptr;

VkDescriptorPool* ComponentsBase::pDescriptorPool = nullptr;
std::vector<VkDescriptorSet>* ComponentsBase::pDescriptorSets = nullptr;

std::vector<VkImage>* ComponentsBase::pSwapChainImages = nullptr;
std::vector<VkBuffer>* ComponentsBase::pUniformBuffers = nullptr;
std::vector<VkDeviceMemory>* ComponentsBase::pUniformBuffersMemory = nullptr;

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

std::vector<VkImage>* ComponentsBase::getSwapChainImages()
{
    return this->pSwapChainImages;
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