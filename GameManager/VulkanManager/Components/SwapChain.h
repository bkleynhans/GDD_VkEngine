#ifndef _SWAPCHAINSUPPORT_H_
#define _SWAPCHAINSUPPORT_H_

#include <algorithm>
#include <optional>
#include <set>
#include <cstdint>

#include "WindowManager/WindowManager.h"
#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/QueueFamilyIndices.h"


// Swap Chains description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 77
    1) Not all graphics cards are capable of presenting images directly to a screen for
            various reasons, for example because they are designed for servers and don’t
            have any display outputs. Secondly, since image presentation is heavily tied
            into the window system and the surfaces associated with windows, it is not
            actually part of the Vulkan core. You have to enable the VK_KHR_swapchain
            device extension after querying for its support.

   Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 79
    2) Just checking if a swap chain is available is not sufficient, because it may not
            actually be compatible with our window surface. Creating a swap chain also
            involves a lot more settings than instance and device creation, so we need to
            query for some more details before we’re able to proceed.

            There are basically three kinds of properties we need to check:
            • Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
            • Surface formats (pixel format, color space)
            • Available presentation modes

    Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 81
    3) If the swapChainAdequate conditions were met then the support is definitely
            sufficient, but there may still be many different modes of varying optimality.
            We’ll now write a couple of functions to find the right settings for the best
            possible swap chain.
            
            There are three types of settings to determine:
            • Surface format (color depth)
            • Presentation mode (conditions for “swapping” images to the screen)
            • Swap extent (resolution of images in swap chain)

            For each of these settings we’ll have an ideal value in mind that we’ll go with if
            it’s available and otherwise we’ll create some logic to find the next best thing.
*/

class SwapChain :
    public ComponentsBase
{
public:
    SwapChain();
    SwapChain(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface);
    ~SwapChain();

    bool extensionsSupported();
    bool swapChainAdequate();
    void checkDeviceExtensionSupport(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface);
    void querySwapChainSupport(VkPhysicalDevice* pPhysicalDevice, VkSurfaceKHR* pSurface);    
    void createSwapChain(WindowManager* pWindowManager, VkSurfaceKHR* pSurface, QueueFamilyIndices* pIndices);
    
    void chooseSwapSurfaceFormat();
    void chooseSwapPresentMode();
    void chooseSwapExtent(WindowManager* pWindowManager);

    void deleteSwapChainImages();

    VkSwapchainKHR getSwapChain();
    VkFormat getSwapChainImageFormat();

    std::vector<VkImage>* getSwapChainImages();

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
private:
    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;    

    VkSurfaceCapabilitiesKHR capabilities;
    VkExtent2D actualExtent;
    
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR chosenPresentMode;
    VkExtent2D swapChainExtent;

    std::set<std::string>* pRequiredExtensions = nullptr;
    std::vector<VkExtensionProperties>* pAvailableExtensions = nullptr;
    std::vector<VkSurfaceFormatKHR>* pSurfaceFormats = nullptr;
    std::vector<VkPresentModeKHR>* pPresentModes = nullptr;
    std::vector<VkImage>* pSwapChainImages = nullptr;

    bool requiredExtensionsSupported = false;
    bool swapChainIsAdequate = false;

    uint32_t formatCount;
    uint32_t presentModeCount;
    uint32_t imageCount;
};

#endif // _SWAPCHAINSUPPORT_H_