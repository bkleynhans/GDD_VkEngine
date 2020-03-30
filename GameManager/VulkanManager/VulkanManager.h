#ifndef _VULKANMANAGER_H_
#define _VULKANMANAGER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>

#include "WindowManager/WindowManager.h"
#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/GlfwExtensionProperties.h"
#include "VulkanManager/Components/VulkanExtensionProperties.h"
#include "VulkanManager/Components/VulkanLayerProperties.h"
#include "VulkanManager/Components/GpuProperties.h"
#include "VulkanManager/Components/RenderPass.h"
#include "VulkanManager/Components/GraphicsPipeline.h"
#include "VulkanManager/Components/Framebuffers.h"
#include "VulkanManager/Components/CommandBuffers.h"

// Vulkan Manager Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 45
    Firstly we need to initialize the Vulkan library by creating an instance. The
    instance is the connection between the application and the Vulkan library and
    creating it involves specifying some details about your application to the
    driver.
*/
class VulkanManager
{
public:
    VulkanManager(WindowManager* pWindowManager);
    ~VulkanManager();

    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    void createSurface(WindowManager* pWindowManager);
    void createImageViews();
    void createCommandPool();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

private:
    ComponentsBase* pComponentsBase = nullptr;
    GlfwExtensionProperties* pGlfwExtensionProperties = nullptr;
    VulkanExtensionProperties* pVulkanExtensionProperties = nullptr;
    VulkanLayerProperties* pVulkanLayerProperties = nullptr;
    GpuProperties* pGpuProperties = nullptr;
    RenderPass* pRenderPass = nullptr;
    GraphicsPipeline* pGraphicsPipeline = nullptr;
    Framebuffers* pFramebuffers = nullptr;
    CommandBuffers* pCommandBuffers = nullptr;
        
    VkDebugUtilsMessengerEXT debugMessenger;

    std::vector<VkImageView>* pSwapChainImageViews = nullptr;

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
};

#endif // _VULKANMANAGER_H_