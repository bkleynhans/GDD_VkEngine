#ifndef _VULKANMANAGER_H_
#define _VULKANMANAGER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>

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
    void createInstance();
    ~VulkanManager();

private:
    VkInstance instance;
    // VkResult result;                         // --> 001

    VkApplicationInfo appInfo = {};             // Optional
    VkInstanceCreateInfo createInfo = {};       // Required

    const char** glfwExtensions = nullptr;

    uint32_t glfwExtensionCount = 0;
    uint32_t extensionCount = 0;
    uint32_t layerCount = 0;

    std::vector<VkExtensionProperties>* extensions = nullptr;    
    std::vector<VkLayerProperties>* availableLayers = nullptr;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    bool checkValidationLayerSupport();
};

#endif // _VULKANMANAGER_H_