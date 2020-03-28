#ifndef _SWAPCHAINS_H_
#define _SWAPCHAINS_H_

#include <optional>
#include <set>

#include "VulkanManager/ComponentsBase.h"

// Swap Chains description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 77
    Not all graphics cards are capable of presenting images directly to a screen for
    various reasons, for example because they are designed for servers and don’t
    have any display outputs. Secondly, since image presentation is heavily tied
    into the window system and the surfaces associated with windows, it is not
    actually part of the Vulkan core. You have to enable the VK_KHR_swapchain
    device extension after querying for its support.
*/

class SwapChains :
    public ComponentsBase
{
public:
    SwapChains(VkPhysicalDevice* pPhysicalDevice);
    ~SwapChains();

    void checkDeviceExtensionSupport(VkPhysicalDevice* pPhysicalDevice);
    bool extensionsSupported();

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
private:

    std::vector<VkExtensionProperties>* pAvailableExtensions = nullptr;
    std::set<std::string>* pRequiredExtensions = nullptr;

    bool requiredExtensionsSupported = false;
};

#endif // _SWAPCHAINS_H_