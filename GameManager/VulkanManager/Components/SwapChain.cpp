#include "Swapchain.h"

Swapchain::Swapchain() {}

Swapchain::Swapchain(VkPhysicalDevice* pPhysicalDevice)
{
    this->checkDeviceExtensionSupport(pPhysicalDevice);
}

bool Swapchain::extensionsSupported()
{
    return this->requiredExtensionsSupported;
}

bool Swapchain::swapChainAdequate()
{
    return this->swapChainIsAdequate;
}

VkSwapchainKHR Swapchain::getSwapchain()
{
    return *pSwapchain;
}

VkFormat Swapchain::getSwapChainImageFormat()
{
    return this->swapChainImageFormat;
}

VkSurfaceFormatKHR Swapchain::getSurfaceFormat()
{
    return this->surfaceFormat;
}

VkPresentModeKHR Swapchain::getChosenPresentMode()
{
    return this->chosenPresentMode;
}

VkExtent2D Swapchain::getSwapChainExtent()
{
    return this->swapChainExtent;
}

std::vector<VkImage>* Swapchain::getSwapChainImages()
{
    return this->pSwapChainImages;
}

// Test for required extensions
void Swapchain::checkDeviceExtensionSupport(VkPhysicalDevice* pPhysicalDevice)
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
        this->querySwapChainSupport(pPhysicalDevice);
    }
}

// Populate swap chain support (this object)
void Swapchain::querySwapChainSupport(VkPhysicalDevice* pPhysicalDevice)
{
    // Query basic surface capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*pPhysicalDevice, *pSurface, &this->capabilities);

    // Query supported surface formats
    vkGetPhysicalDeviceSurfaceFormatsKHR(*pPhysicalDevice, *pSurface, &this->formatCount, nullptr);

    if (this->formatCount != 0)
    {
        this->pSurfaceFormats = new std::vector<VkSurfaceFormatKHR>(this->formatCount);

        vkGetPhysicalDeviceSurfaceFormatsKHR(
            *pPhysicalDevice,
            *pSurface,
            &this->formatCount,
            this->pSurfaceFormats->data()
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

    this->swapChainIsAdequate = !this->pSurfaceFormats->empty() && !this->pPresentModes->empty();
}

// Run through the surface formats we found, and see if the required combination is available
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 82 */
void Swapchain::chooseSwapSurfaceFormat()
{
    for (const auto& availableFormat : *this->pSurfaceFormats)
    {
        if ((availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM) && 
            (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
        {
            this->surfaceFormat = availableFormat;
            return;
        }
    }

    // If the desired combination is not available, simply use the "best" option available
    this->surfaceFormat = (*this->pSurfaceFormats)[0];
}

// Choose the presentation mode
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 82-83
    The presentation mode is arguably the most important setting for the swap
    chain, because it represents the actual conditions for showing images to the
    screen.
    
    There are four possible modes available in Vulkan:
    • VK_PRESENT_MODE_IMMEDIATE_KHR: Images submitted by your application
        are transferred to the screen right away, which may result in tearing.
    • VK_PRESENT_MODE_FIFO_KHR: The swap chain is a queue where the display
        takes an image from the front of the queue when the display is refreshed
        and the program inserts rendered images at the back of the queue. If the
        queue is full then the program has to wait. This is most similar to vertical
        sync as found in modern games. The moment that the display is refreshed
        is known as “vertical blank”.
    • VK_PRESENT_MODE_FIFO_RELAXED_KHR: This mode only differs from the
        previous one if the application is late and the queue was empty at the last
        vertical blank. Instead of waiting for the next vertical blank, the image is
        transferred right away when it finally arrives. This may result in visible
        tearing.
    • VK_PRESENT_MODE_MAILBOX_KHR: This is another variation of the second
        mode. Instead of blocking the application when the queue is full, the
        images that are already queued are simply replaced with the newer ones.
        This mode can be used to implement triple buffering, which allows you to
        avoid tearing with significantly less latency issues than standard vertical
        sync that uses double buffering.

    Only the VK_PRESENT_MODE_FIFO_KHR mode is guaranteed to be available, so
    we’ll again have to write a function that looks for the best mode that is available:
*/
void Swapchain::chooseSwapPresentMode()
{
    for (const auto& availablePresentMode : *this->pPresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            this->chosenPresentMode = availablePresentMode;
            return;
        }
    }

    this->chosenPresentMode = VK_PRESENT_MODE_FIFO_KHR;
}

// Choose the swap extent (resolution of the swap chain) to use
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 83-84
    The swap extent is the resolution of the swap chain images and it’s almost
    always exactly equal to the resolution of the window that we’re drawing to. The
    range of the possible resolutions is defined in the VkSurfaceCapabilitiesKHR
    structure. Vulkan tells us to match the resolution of the window by setting
    the width and height in the currentExtent member.
*/

void Swapchain::chooseSwapExtent(WindowManager* pWindowManager)
{
    if (this->capabilities.currentExtent.width != UINT32_MAX)
    {
        this->swapChainExtent = this->capabilities.currentExtent;
    }
    else
    {
        VkExtent2D actualExtent = { pWindowManager->getWidth(), pWindowManager->getHeight() };

        // Clamp width and height
        /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 84
            The max and min functions are used here to clamp the value of WIDTH and HEIGHT
            between the allowed minimum and maximum extents that are supported by the
            implementation. Make sure to include the <algorithm> header to use them.
        */
        this->actualExtent.width =
            std::max(
                this->capabilities.minImageExtent.width,
                std::min(
                    this->capabilities.maxImageExtent.width,
                    this->actualExtent.width
                )
            );

        this->actualExtent.height =
            std::max(
                this->capabilities.minImageExtent.height,
                std::min(
                    this->capabilities.maxImageExtent.height,
                    this->actualExtent.height
                )
            );

        this->swapChainExtent = this->actualExtent;
    }        
}

// Create the swap chain
void Swapchain::createSwapChain(WindowManager* pWindowManager, QueueFamilyIndices* pIndices)
{
    this->chooseSwapSurfaceFormat();
    this->chooseSwapPresentMode();
    this->chooseSwapExtent(pWindowManager);

    // Specify the minimum number of images required for the swap chain
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 85
        Aside from these properties we also have to decide how many images we would
        like to have in the swap chain. The implementation specifies the minimum
        number that it requires to function

        However, simply sticking to this minimum means that we may sometimes have
        to wait on the driver to complete internal operations before we can acquire
        another image to render to. Therefore it is recommended to request at least one
        more image than the minimum
    */
    this->imageCount = this->capabilities.minImageCount + 1;

    // Ensure we do not exceed the maximum number of images for the swap chain
    if ((this->capabilities.maxImageCount > 0) &&
        (this->imageCount > this->capabilities.maxImageCount))
    {
        this->imageCount = this->capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = *pSurface;

    createInfo.minImageCount = this->imageCount;
    createInfo.imageFormat = this->surfaceFormat.format;
    createInfo.imageColorSpace = this->surfaceFormat.colorSpace;
    createInfo.imageExtent = this->swapChainExtent;

    // imageArrayLayers always 1, unless developing a stereoscopic 3D application
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 86
        The imageArrayLayers specifies the amount of layers each image consists of.
        This is always 1 unless you are developing a stereoscopic 3D application. The
        imageUsage bit field specifies what kind of operations we’ll use the images in
        the swap chain for.
    */
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    // Specify how to handle swap chain images
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 86
        We need to specify how to handle swap chain images that will be used
        across multiple queue families. That will be the case in our application if the
        graphics queue family is different from the presentation queue. We’ll be drawing
        on the images in the swap chain from the graphics queue and then submitting
        them on the presentation queue.
        
        There are two ways to handle images that are accessed from multiple queues:
        • VK_SHARING_MODE_EXCLUSIVE: An image is owned by one queue family
            at a time and ownership must be explicitly transfered before using it in
            another queue family. This option offers the best performance.
        • VK_SHARING_MODE_CONCURRENT: Images can be used across multiple queue
            families without explicit ownership transfers.

        If the queue families differ, then we’ll be using the concurrent mode in this
        tutorial to avoid having to do the ownership chapters, because these involve some
        concepts that are better explained at a later time. Concurrent mode requires
        you to specify in advance between which queue families ownership will be shared
        using the queueFamilyIndexCount and pQueueFamilyIndices parameters. If
        the graphics queue family and presentation queue family are the same, which
        will be the case on most hardware, then we should stick to exclusive mode,
        because concurrent mode requires you to specify at least two distinct queue
        families.
    */
    uint32_t queueFamilyIndices[] = { pIndices->graphicsFamily.value(), pIndices->presentFamily.value() };

    if (pIndices->graphicsFamily != pIndices->presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    // Specify if we want to apply a transform in the swap chain
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 86
        We can specify that a certain transform should be applied to images in the
        swap chain if it is supported (supportedTransforms in capabilities), like a
        90 degree clockwise rotation or horizontal flip. To specify that you do not want
        any transformation, simply specify the current transformation.
    */
    createInfo.preTransform = this->capabilities.currentTransform;

    // Specify whether alpha channel should be used for blending
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 86
        The compositeAlpha field specifies if the alpha channel should be used for blending
        with other windows in the window system. You’ll almost always want to
        simply ignore the alpha channel, hence VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR.
    */
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    createInfo.presentMode = this->chosenPresentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;
    
    pSwapchain = new VkSwapchainKHR();

    /*if (vkCreateSwapchainKHR(*pDevice, &createInfo, nullptr, &this->swapChain) != VK_SUCCESS)*/
    if (vkCreateSwapchainKHR(*pDevice, &createInfo, nullptr, pSwapchain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    /*vkGetSwapchainImagesKHR(*pDevice, this->swapChain, &this->imageCount, nullptr);*/
    vkGetSwapchainImagesKHR(*pDevice, *pSwapchain, &this->imageCount, nullptr);
    this->pSwapChainImages = new std::vector<VkImage>(this->imageCount);
    vkGetSwapchainImagesKHR(*pDevice, *pSwapchain, &this->imageCount, this->pSwapChainImages->data());
    /*vkGetSwapchainImagesKHR(*pDevice, this->swapChain, &this->imageCount, this->pSwapChainImages->data());*/

    this->swapChainImageFormat = this->surfaceFormat.format;
}

void Swapchain::deleteSwapChainImages()
{
    std::vector<VkImage>().swap(*this->pSwapChainImages);
}

Swapchain::~Swapchain()
{
    // We created with the 'new' keyword so we need to clear memory
    delete pSwapchain;

    std::vector<VkSurfaceFormatKHR>().swap(*this->pSurfaceFormats);
    std::vector<VkPresentModeKHR>().swap(*this->pPresentModes);
    std::set<std::string>().swap(*this->pRequiredExtensions);
    std::vector<VkExtensionProperties>().swap(*this->pAvailableExtensions);
}