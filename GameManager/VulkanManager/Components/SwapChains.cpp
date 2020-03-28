#include "SwapChains.h"

SwapChains::SwapChains(VkPhysicalDevice* pPhysicalDevice)
{
    this->checkDeviceExtensionSupport(pPhysicalDevice);
}

bool SwapChains::extensionsSupported()
{
    return this->requiredExtensionsSupported;
}

// Test for required extensions
void SwapChains::checkDeviceExtensionSupport(VkPhysicalDevice* pPhysicalDevice)
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

    this->requiredExtensionsSupported =  this->pRequiredExtensions->empty();
}

SwapChains::~SwapChains()
{
    // We created with the 'new' keyword so we need to clear memory
    std::set<std::string>().swap(*this->pRequiredExtensions);
    std::vector<VkExtensionProperties>().swap(*this->pAvailableExtensions);
}