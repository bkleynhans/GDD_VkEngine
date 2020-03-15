#include "VulkanManager.h"

VulkanManager::VulkanManager()
{
    this->pGlfwExtensionProperties = &GlfwExtensionProperties();
    this->pVulkanExtensionProperties = &VulkanExtensionProperties();
    this->pVulkanLayerProperties = &VulkanLayerProperties();

    this->createInstance();
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
    this->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    this->appInfo.pApplicationName = "Hello Triangle";
    this->appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    this->appInfo.pEngineName = "No Engine";
    this->appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    this->appInfo.apiVersion = VK_API_VERSION_1_0;

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        The createInfo struct information is NOT optional and tells the Vulkan
        driver which global extensions and validation layers we want to use.
    */    
    this->createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    this->createInfo.pApplicationInfo = &this->appInfo;

    if (enableValidationLayers)
    {
        this->pGlfwExtensionProperties->addMessageCallback();
        this->createInfo.enabledExtensionCount = static_cast<uint32_t>(this->pGlfwExtensionProperties->extensions.size());
        this->createInfo.ppEnabledExtensionNames = this->pGlfwExtensionProperties->extensions.data();
    }
    else
    {
        this->createInfo.enabledExtensionCount = this->pGlfwExtensionProperties->count;
        this->createInfo.ppEnabledExtensionNames = this->pGlfwExtensionProperties->glfwExtensions;
    }
    
    this->createInfo.enabledLayerCount = 0;

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 52
        Add validation layer support to VkInstanceCreateInfo struct
    */
    if (enableValidationLayers)
    {        
        this->createInfo.enabledLayerCount = static_cast<uint32_t>(this->pVulkanLayerProperties->validationLayers.size());
        this->createInfo.ppEnabledLayerNames = this->pVulkanLayerProperties->validationLayers.data();
    }
    else
    {
        this->createInfo.enabledLayerCount = 0;
    }

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        We've now specified everything Vulkan needs to create an instance so
        we can issue the vkCreateInstance call
    */
    // --> 001 - Store the result of the process in the result variable
    //this->result = vkCreateInstance(&this->createInfo, nullptr, &this->instance);

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        Nearly all Vulkan functions return a value of type VkResult that is either
        VK_SUCCESS or an error code.  To check if the instance was created
        successfully, we can either store the result in the 'result' variable (001), or
        we can just use a check for the success value instead (002).
    */
    // --> 002 - Handle the result of the process and throw an error if required
    if (vkCreateInstance(&this->createInfo, nullptr, &this->instance) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance");
    }

    std::cout << "Vulkan Manager Created" << std::endl;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanManager::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    std::cerr << "validation layer : " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VulkanManager::~VulkanManager()
{
    vkDestroyInstance(this->instance, nullptr);

    delete this->pVulkanLayerProperties;
    delete this->pVulkanExtensionProperties;
    delete this->pGlfwExtensionProperties;

    std::cout << "Vulkan Manager Destroyed" << std::endl;
}


