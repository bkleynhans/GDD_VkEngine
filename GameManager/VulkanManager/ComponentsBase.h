#ifndef _COMPONENTSBASE_H_
#define _COMPONENTSBASE_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>

class ComponentsBase
{
public:
    ComponentsBase();
    ~ComponentsBase();

    VkDevice getDevice();
    VkInstance getInstance();
    VkSwapchainKHR getSwapchain();
    VkPhysicalDevice getPhysicalDevice();
    VkQueue getGraphicsQueue();
    VkQueue getPresentQueue();

    static VkInstance* pInstance;
    static VkSurfaceKHR* pSurface;
    static VkQueue* pGraphicsQueue;
    static VkQueue* pPresentQueue;
    static VkSwapchainKHR* pSwapchain;
    static VkRenderPass* pRenderPass;
    static VkPipelineLayout* pPipelineLayout;
    static VkPipeline* pGraphicsPipeline;
    static VkCommandPool* pCommandPool;
    
    
    uint32_t count = 0;
        
// STRUCT for Validation Layers
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 50
    Add two configuration variables to the program to specify the layers
    to enable and whether to enable them or not. I’ve chosen to base that value
    on whether the program is being compiled in debug mode or not. The NDEBUG
    macro is part of the C++ standard and means “not debug”.
*/
#ifdef NDEBUG
    static const bool enableValidationLayers = false;
#else
    static const bool enableValidationLayers = true;
#endif

protected:
    static VkDevice* pDevice;
    static VkPhysicalDevice* pPhysicalDevice;
};

#endif // _COMPONENTSBASE_H_