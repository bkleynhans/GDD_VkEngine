#include "SwapChain.h"

SwapChain::SwapChain(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface)
{
    this->checkDeviceExtensionSupport(pPhysicalDevice, pSurface);
}

bool SwapChain::extensionsSupported()
{
    return this->requiredExtensionsSupported;
}

bool SwapChain::swapChainAdequate()
{
    return this->swapChainIsAdequate;
}

// Test for required extensions
void SwapChain::checkDeviceExtensionSupport(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface)
{
    // Query the number of extensions available to device
    vkEnumerateDeviceExtensionProperties(*pPhysicalDevice, nullptr, &this->count, nullptr);

    this->pAvailableExtensions = new std::vector<VkExtensionProperties>(this->count);

    // Get data pertaining to the discovered extensions
    vkEnumerateDeviceExtensionProperties(*pPhysicalDevice, nullptr, &this->count, this->pAvailableExtensions->data());

    this->pRequiredExtensions = new std::set<std::string>(this->deviceExtensions.begin(), this->deviceExtensions.end());

    // Loop and test for extensions
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 78
        Modify the body of the function to enumerate the extensions and check if all of
        the required extensions are amongst them.
    */
    for (const auto& extension : *this->pAvailableExtensions)
    {
        this->pRequiredExtensions->erase(extension.extensionName);
    }

    this->requiredExtensionsSupported = this->pRequiredExtensions->empty();

    if (this->extensionsSupported())
    {
        this->querySwapChainSupport(pPhysicalDevice, pSurface);
    }
}

// Populate swap chain support (this object)
void SwapChain::querySwapChainSupport(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface)
{
    // Query basic surface capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*pPhysicalDevice, *pSurface, &this->capabilities);

    // Query supported surface formats
    vkGetPhysicalDeviceSurfaceFormatsKHR(*pPhysicalDevice, *pSurface, &this->formatCount, nullptr);

    if (this->formatCount != 0)
    {
        this->pFormats = new std::vector<VkSurfaceFormatKHR>(this->formatCount);

        vkGetPhysicalDeviceSurfaceFormatsKHR(
            *pPhysicalDevice,
            *pSurface,
            &this->formatCount,
            this->pFormats->data()
        );
    }

    // Query the supported presentation modes
    vkGetPhysicalDeviceSurfacePresentModesKHR(*pPhysicalDevice, *pSurface, &this->presentModeCount, nullptr);

    if (this->presentModeCount != 0)
    {
        this->pPresentModes = new std::vector<VkPresentModeKHR>(this->presentModeCount);

        vkGetPhysicalDeviceSurfacePresentModesKHR(
            *pPhysicalDevice,
            *pSurface,
            &this->presentModeCount,
            this->pPresentModes->data()
        );
    }

    this->swapChainIsAdequate = !this->pFormats->empty() && !this->pPresentModes->empty();
}

SwapChain::~SwapChain()
{
    // We created with the 'new' keyword so we need to clear memory
    std::vector<VkSurfaceFormatKHR>().swap(*this->pFormats);
    std::vector<VkPresentModeKHR>().swap(*this->pPresentModes);
    std::set<std::string>().swap(*this->pRequiredExtensions);
    std::vector<VkExtensionProperties>().swap(*this->pAvailableExtensions);
}