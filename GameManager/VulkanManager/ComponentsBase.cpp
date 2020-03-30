#include "ComponentsBase.h"

VkInstance* ComponentsBase::pInstance = nullptr;
VkSurfaceKHR* ComponentsBase::pSurface = nullptr;
VkRenderPass* ComponentsBase::pRenderPass = nullptr;
VkPipelineLayout* ComponentsBase::pPipelineLayout = nullptr;
VkPipeline* ComponentsBase::pGraphicsPipeline = nullptr;

VkDevice* ComponentsBase::pDevice = nullptr;
VkPhysicalDevice* ComponentsBase::pPhysicalDevice = VK_NULL_HANDLE;

ComponentsBase::ComponentsBase()
{
    
}

VkDevice ComponentsBase::getDevice()
{
    return *pDevice;
}

VkPhysicalDevice ComponentsBase::getPhysicalDevice()
{
    return *pPhysicalDevice;
}

ComponentsBase::~ComponentsBase()
{

}