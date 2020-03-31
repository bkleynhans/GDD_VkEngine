#include "GpuProperties.h"

GpuProperties::GpuProperties(
    VulkanLayerProperties* pVulkanLayerProperties, WindowManager* pWindowManager)
{   
    pDevice = new VkDevice();
    pPhysicalDevice = new VkPhysicalDevice();

    this->pSwapchain = new Swapchain();

    this->pickPhysicalDevice(pSurface);

    this->pIndices = new QueueFamilyIndices(pPhysicalDevice);

    this->pLogicalDevice = new LogicalDevice(
        pVulkanLayerProperties,
        this->pIndices,
        this->pSwapchain            // This is a reference to a predefined list in the Swapchain class
    );

    this->pSwapchain = new Swapchain(pPhysicalDevice);
    this->pSwapchain->createSwapChain(pWindowManager, this->pIndices);
}

// Basic Support
/* If the only requirement for the graphics card is Vulkan, and shader
    support.  The following two methods look at available devices and chooses
    the first device that supports those features.  If you want to look at
    all available devices, rate them according to capabilities and then choose
    the best one, use the current "un-commented" section of code.  Also uncomment
    the "bool isDeviceSuitable(VkPhysicalDevice device);" function in the header file.
*/
//// Find a list of graphics cards in the machine that have Vulkan support
//void GpuProperties::pickPhysicalDevice(VkInstance* pInstance)
//{
//    // Query the number of graphics cards with Vulkan support in the computer
//    vkEnumeratePhysicalDevices(*pInstance, &this->count, nullptr);
//
//    // If there are no supporting GPU's, return
//    if (this->count == 0)
//    {
//        throw std::runtime_error("failed to find GPUs with Vulkan support!");
//    }
//
//    // If there are GPU's with vulkan support, create an array and store them
//    this->pDevices = new std::vector<VkPhysicalDevice>(this->count);
//    vkEnumeratePhysicalDevices(*pInstance, &this->count, this->pDevices->data());
//
//    // Determine which of the devices that were found, support the graphics
//    // actions we want to perform
//    for (const auto& device : *this->pDevices)
//    {
//        if (this->isDeviceSuitable(device))
//        {
//            this->physicalDevice = device;
//            break;
//        }
//    }
//
//    // Throw exception if no suitable GPU was found
//    if (this->physicalDevice == VK_NULL_HANDLE)
//    {
//        throw std::runtime_error("failed to find a suitable GPU!");
//    }
//}
//
//// Determines whether the supplied graphics card supports the features we need
//bool GpuProperties::isDeviceSuitable(VkPhysicalDevice device)
//{
//    // Device Properties
//    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 61
//        Basic device properties like the name, type and supported Vulkan version can
//        be queried using vkGetPhysicalDeviceProperties.
//    */
//    vkGetPhysicalDeviceProperties(device, &this->deviceProperties);
//
//    // Device Features
//    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 62
//        The support for optional features like texture compression, 64 bit floats and
//        multi viewport rendering (useful for VR) can be queried using
//        vkGetPhysicalDeviceFeatures.
//    */
//    vkGetPhysicalDeviceFeatures(device, &this->deviceFeatures);
//
//    // Basic check, geometry shader support is sufficient
//    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 62
//        Let’s say we consider our application only usable for dedicated
//        graphics cards that support geometry shaders.  Then the following
//        return statement would be sufficient.
//    */
//    return this->deviceProperties.deviceType ==
//        VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
//}

// Advanced Support
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 62
    Instead of just checking if a device is suitable or not and going with the first one,
    you could also give each device a score and pick the highest one. That way you
    could favor a dedicated graphics card by giving it a higher score, but fall back
    to an integrated GPU if that’s the only available one.
*/
void GpuProperties::pickPhysicalDevice(VkSurfaceKHR* pSurface)
{
    // Query the number of graphics cards with Vulkan support in the computer
    vkEnumeratePhysicalDevices(*pInstance, &this->count, nullptr);

    // If there are no supporting GPU's, return
    if (this->count == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    // If there are GPU's with vulkan support, create an array and store them
    this->pDevices = new std::vector<VkPhysicalDevice>(this->count);
    vkEnumeratePhysicalDevices(*pInstance, &this->count, this->pDevices->data());

    pCandidates = new std::multimap<int, VkPhysicalDevice>();
    pCandidate = new VkPhysicalDevice;

    // Use an ordered map to automatically sort candidates by increasing score
    for (const auto& device : *this->pDevices)
    {
        int score = this->rateDeviceSuitability(device);
        *this->pCandidates->insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (this->pCandidates->rbegin()->first > 0)
    {
        *pCandidate = this->pCandidates->rbegin()->second;

        if (!deviceIsSuitable(pCandidate))
        {            
            throw std::runtime_error("failed to find a suitable GPU!");
        }

        pPhysicalDevice = pCandidate;
    }
    else
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

// Determines whether the supplied graphics card supports the features we need
int GpuProperties::rateDeviceSuitability(VkPhysicalDevice candidate)
{
    // Device Properties
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 61
        Basic device properties like the name, type and supported Vulkan version can
        be queried using vkGetPhysicalDeviceProperties.
    */
    vkGetPhysicalDeviceProperties(candidate, &this->deviceProperties);

    // Device Features
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 62
        The support for optional features like texture compression, 64 bit floats and
        multi viewport rendering (useful for VR) can be queried using
        vkGetPhysicalDeviceFeatures.
    */
    vkGetPhysicalDeviceFeatures(candidate, &this->deviceFeatures);

    int score = 0;

    // Device Performance
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 62
        Discrete GPUs have a significant performance advantage.
    */
    if (this->deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }

    // Device Graphics Quality
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 62
        Maximum possible size of textures affects graphics quality.
    */
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader)
    {
        score = 0;
    }

    return score;
}

// Look for queues that support the types of commands we require support for.
// Even though we have a static physical device, they static variable is for completed
// decisions.  In this case we're still evaluating the devices
bool GpuProperties::deviceIsSuitable(VkPhysicalDevice* pCandidate)
{
    QueueFamilyIndices indices = QueueFamilyIndices(pCandidate);
    Swapchain swapChains = Swapchain(pCandidate);
    
    return indices.isComplete() && swapChains.extensionsSupported() && swapChains.swapChainAdequate();
}

GpuProperties::~GpuProperties()
{
    // We created with the 'new' keyword so we need to clear memory
    // Delete swapchain and conditional components
    this->pSwapchain->deleteSwapChainImages();
    /*vkDestroySwapchainKHR(*pDevice, this->pSwapchain->getSwapchain(), nullptr);*/
    vkDestroySwapchainKHR(*pDevice, this->pSwapchain->getSwapchain(), nullptr);

    // Delete remaining items
    vkDestroyDevice(*pDevice, nullptr);    
    delete this->pSwapchain;
    delete this->pIndices;

    delete this->pCandidate;
    this->pCandidates->clear();
    std::vector<VkPhysicalDevice>().swap(*this->pDevices);
}