#ifndef _SWAPCHAINSUPPORT_H_
#define _SWAPCHAINSUPPORT_H_

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

   Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 79
    Just checking if a swap chain is available is not sufficient, because it may not
    actually be compatible with our window surface. Creating a swap chain also
    involves a lot more settings than instance and device creation, so we need to
    query for some more details before we’re able to proceed.

    There are basically three kinds of properties we need to check:
    • Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
    • Surface formats (pixel format, color space)
    • Available presentation modes
*/

class SwapChain :
    public ComponentsBase
{
public:
    SwapChain(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface);
    ~SwapChain();

    bool extensionsSupported();
    bool swapChainAdequate();
    void checkDeviceExtensionSupport(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface);
    void querySwapChainSupport(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface);

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
private:

    VkSurfaceCapabilitiesKHR capabilities;

    std::set<std::string>* pRequiredExtensions = nullptr;
    std::vector<VkExtensionProperties>* pAvailableExtensions = nullptr;
    std::vector<VkSurfaceFormatKHR>* pFormats = nullptr;
    std::vector<VkPresentModeKHR>* pPresentModes = nullptr;

    bool requiredExtensionsSupported = false;
    bool swapChainIsAdequate = false;

    uint32_t formatCount;
    uint32_t presentModeCount;

};

#endif // _SWAPCHAINSUPPORT_H_