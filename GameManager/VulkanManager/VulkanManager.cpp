#include "VulkanManager/DebugTools.cpp"
#include "VulkanManager.h"

VulkanManager::VulkanManager(WindowManager* pWindowManager)
{   
    this->pGlfwExtensionProperties = new GlfwExtensionProperties();
    this->pVulkanExtensionProperties = new VulkanExtensionProperties();
    this->pVulkanLayerProperties = new VulkanLayerProperties();

    this->createInstance();
    this->setupDebugMessenger();
    this->createSurface(pWindowManager);

    this->pGpuProperties = new GpuProperties(&this->instance, this->pVulkanLayerProperties, &this->surface);    
}

// createInstance Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 45
    In order to create a Vulkan instance, we need to fill in a struct with
    some information about the application.
*/
void VulkanManager::createInstance()
{
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 52
        Check if required validation layers are available for use by
        the program - Final part of Validation Layers tutorial starting on
        page 49.
    */
    if (enableValidationLayers && !this->pVulkanLayerProperties->checkValidationLayerSupport())
    {
        throw std::runtime_error("validation layers requested, but not available");
    }

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 45
        The appInfo is optional, but may provide some useful information to
        the driver to optimize this specific appliation
    */
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        The createInfo struct information is NOT optional and tells the Vulkan
        driver which global extensions and validation layers we want to use.
    */
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 52
        Add validation layer support to VkInstanceCreateInfo struct
    */
    if (enableValidationLayers)
    {
        this->pGlfwExtensionProperties->addMessageCallback();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(this->pGlfwExtensionProperties->pExtensions.size());
        createInfo.ppEnabledExtensionNames = this->pGlfwExtensionProperties->pExtensions.data();

        createInfo.enabledLayerCount = static_cast<uint32_t>(this->pVulkanLayerProperties->validationLayers.size());
        createInfo.ppEnabledLayerNames = this->pVulkanLayerProperties->validationLayers.data();

        this->populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else
    {
        createInfo.enabledExtensionCount = this->pGlfwExtensionProperties->count;
        createInfo.ppEnabledExtensionNames = this->pGlfwExtensionProperties->glfwExtensions;

        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        Nearly all Vulkan functions return a value of type VkResult that is either
        VK_SUCCESS or an error code.  To check if the instance was created
        successfully, we can either store the result in the 'result' variable (001), or
        we can just use a check for the success value instead (002).
    */
    // Handle the result of the process and throw an error if required
    if (vkCreateInstance(&createInfo, nullptr, &this->instance) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance");
    }
}

void VulkanManager::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback = debugCallback;
}

void VulkanManager::setupDebugMessenger()
{
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    this->populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(this->instance, &createInfo, nullptr, &this->debugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VulkanManager::createSurface(WindowManager* pWindowManager)
{
    if (glfwCreateWindowSurface(this->instance, pWindowManager->pWindow, nullptr, &this->surface) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create window surface!");
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanManager::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
    std::cerr << "validation layer : " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VulkanManager::~VulkanManager()
{
    if (enableValidationLayers)
    {
        DestroyDebugUtilsMessengerEXT(this->instance, this->debugMessenger, nullptr);
    }

    delete this->pGpuProperties;

    vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
    vkDestroyInstance(this->instance, nullptr);

    delete this->pVulkanLayerProperties;
    delete this->pVulkanExtensionProperties;
    delete this->pGlfwExtensionProperties;    
}