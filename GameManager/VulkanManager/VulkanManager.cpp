#include "VulkanManager.h"

VulkanManager::VulkanManager()
{
    this->createInstance();
}

// createInstance Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 45
    In order to create a Vulkan instance, we need to fill in a struct with
    some information about the application.
*/

void VulkanManager::createInstance()
{
    if (enableValidationLayers && !checkValidationLayerSupport())
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

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        Because Vulkan is a platform agnostic API, we need to specify the desired
        global extensions in order to interface with the window system.  GLFW has
        a handy built-in function that returns the extension(s) it needs to do that
        which we can pass to the struct.
    */    
    this->glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    this->createInfo.enabledExtensionCount = this->glfwExtensionCount;
    this->createInfo.ppEnabledExtensionNames = this->glfwExtensions;
    this->createInfo.enabledLayerCount = 0;

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 52
        Add validation layer support to VkInstanceCreateInfo struct
    */
    if (enableValidationLayers)
    {
        this->createInfo.enabledLayerCount = static_cast<uint32_t>(this->validationLayers.size());
        this->createInfo.ppEnabledLayerNames = this->validationLayers.data();
    }
    else
    {
        this->createInfo.enabledLayerCount = 0;
    }

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 47
        If you look at the vkCreateInstance documentation then you'll see that one
        of the possible error codes is VK_ERROR_EXTENSION_NOT_SUPPORTED. To retrieve
        a list of supported extensions becore creating an instance, there's the
        vkEnumerateInstanceExtensionProperties function.  It takes a pointer to a
        variable that stores the number of extensions and an array of
        VkExtensionProperties to store details of the extensions.
    */
    vkEnumerateInstanceExtensionProperties(nullptr, &this->extensionCount, nullptr);

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 47
        Now allocate an array to hold the extension details
    */
    this->extensions = new std::vector<VkExtensionProperties>(extensionCount);

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 47
        Now we can query the extension details
    */
    vkEnumerateInstanceExtensionProperties(nullptr, &this->extensionCount, this->extensions->data());

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        We can list the supported extensions with a for-loop to display some
        details about Vulkan support
    */
    std::cout << std::endl;
    std::cout << "Supported Extensions : " << std::endl;
    for (const auto& extension : *this->extensions)
    {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
    std::cout << std::endl;

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

// Validation Layers
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
    The Vulkan API is designed around the idea of minimal driver overhead and one
    of the manifestations of that goal is that there is very limited error checking in
    the API by default. Even mistakes as simple as setting enumerations to incorrect
    values or passing null pointers to required parameters are generally not explicitly
    handled and will simply result in crashes or undefined behavior. Because Vulkan
    requires you to be very explicit about everything you’re doing, it’s easy to make
    many small mistakes like using a new GPU feature and forgetting to request it
    at logical device creation time.

    However, that doesn’t mean that these checks can’t be added to the API. Vulkan
    introduces an elegant system for this known as validation layers. Validation
    layers are optional components that hook into Vulkan function calls to apply
    additional operations.
*/
bool VulkanManager::checkValidationLayerSupport()
{
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 51
        List all of the available layers using the vkEnumerateInstanceLayerProperties
        function.  Its usage is identical to that of 
        vkEnumerateInstanceExtensionProperties used above.
    */
    vkEnumerateInstanceLayerProperties(&this->layerCount, nullptr);

    this->availableLayers = new std::vector<VkLayerProperties>(layerCount);

    vkEnumerateInstanceLayerProperties(&this->layerCount, this->availableLayers->data());

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 51
        Check if all of the layers in validationLayers exist in the
        availableLayers list.
    */
    for (const char* layerName : this->validationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : *this->availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

VulkanManager::~VulkanManager()
{
    // We created with the 'new' keyword so we need to clear memory
    std::vector<VkExtensionProperties>().swap(*this->extensions);
    std::vector<VkLayerProperties>().swap(*this->availableLayers);

    vkDestroyInstance(this->instance, nullptr);    

    std::cout << "Vulkan Manager Destroyed" << std::endl;
}


