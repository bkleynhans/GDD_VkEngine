#ifndef _VULKANMANAGER_H_
#define _VULKANMANAGER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>

#include "VulkanManager/SupportedComponents/GlfwExtensionProperties.h"
#include "VulkanManager/SupportedComponents/VulkanExtensionProperties.h"
#include "VulkanManager/SupportedComponents/VulkanLayerProperties.h"
#include "VulkanManager/SupportedComponents/GpuProperties.h"

// STRUCT for Validation Layers
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 50
    Add two configuration variables to the program to specify the layers
    to enable and whether to enable them or not. I’ve chosen to base that value
    on whether the program is being compiled in debug mode or not. The NDEBUG
    macro is part of the C++ standard and means “not debug”.
*/
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

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
    VulkanManager();
    ~VulkanManager();

    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

private:
    GlfwExtensionProperties* pGlfwExtensionProperties = nullptr;
    VulkanExtensionProperties* pVulkanExtensionProperties = nullptr;
    VulkanLayerProperties* pVulkanLayerProperties = nullptr;
    GpuProperties* pGpuProperties = nullptr;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
};

#endif // _VULKANMANAGER_H_