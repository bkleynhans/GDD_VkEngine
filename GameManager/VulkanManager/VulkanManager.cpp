#include "VulkanManager/DebugTools.cpp"
#include "VulkanManager.h"

VulkanManager::VulkanManager(WindowManager* pWindowManager, EntityManager* pEntityManager)
{   
    this->pComponentsBase = new ComponentsBase();
    this->pComponentsBase->setPWindowManager(pWindowManager);
    this->pComponentsBase->setPEntityManager(pEntityManager);

    this->pGlfwExtensionProperties = new GlfwExtensionProperties();
    this->pVulkanExtensionProperties = new VulkanExtensionProperties();
    this->pVulkanLayerProperties = new VulkanLayerProperties();

    this->pComponentsBase->pInstance = new VkInstance;
    this->pComponentsBase->pSurface = new VkSurfaceKHR;

    this->createInstance();
    this->setupDebugMessenger();
    this->createSurface();

    // Interrogate the graphics card and define graphics card parameters
    this->pGpuProperties = new GpuProperties(
        this->pVulkanLayerProperties
    );

    this->createImageViews();

    this->pRenderPass = new RenderPass(this->pGpuProperties);
    this->pGraphicsPipeline = new GraphicsPipeline(this->pGpuProperties);
    this->pFramebuffers = new Framebuffers(this->pGpuProperties, this->pSwapChainImageViews);
    this->pVertexBuffer = new VertexBuffer();

    this->createCommandPool();

    this->pCommandBuffers = new CommandBuffers(this->pGpuProperties, this->pFramebuffers);

    this->createSyncObjects();
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

    // Handle the result of the process and throw an error if required
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        Nearly all Vulkan functions return a value of type VkResult that is either
        VK_SUCCESS or an error code.  To check if the instance was created
        successfully, we can either store the result in the 'result' variable (001), or
        we can just use a check for the success value instead (002).
    */    
    if (vkCreateInstance(&createInfo, nullptr, this->pComponentsBase->pInstance) != VK_SUCCESS)
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

    if (CreateDebugUtilsMessengerEXT(*this->pComponentsBase->pInstance, &createInfo, nullptr, &this->debugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VulkanManager::createSurface()
{
    if (glfwCreateWindowSurface(*this->pComponentsBase->pInstance, pComponentsBase->getPWindow(), nullptr, this->pComponentsBase->pSurface) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create window surface!");
    }
}

void VulkanManager::createImageViews()
{
    size_t sizeOfSwapChainImages = this->pGpuProperties->pSwapchain->getSwapChainImages()->size();

    this->pSwapChainImageViews = new std::vector<VkImageView>(sizeOfSwapChainImages);

    for (size_t i = 0; i < sizeOfSwapChainImages; i++)
    {
        VkImageViewCreateInfo createInfo = {};

        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = (*this->pGpuProperties->pSwapchain->getSwapChainImages())[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = this->pGpuProperties->pSwapchain->getSwapChainImageFormat();
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(this->pGpuProperties->getDevice(), &createInfo, nullptr, &(*this->pSwapChainImageViews)[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void VulkanManager::createCommandPool()
{
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = this->pGpuProperties->pIndices->graphicsFamily.value();

    this->pComponentsBase->pCommandPool = new VkCommandPool();

    if (vkCreateCommandPool(this->getDevice(), &poolInfo, nullptr, this->pComponentsBase->pCommandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

void VulkanManager::createSyncObjects()
{
    this->pImageAvailableSemaphores = new std::vector<VkSemaphore>(this->MAX_FRAMES_IN_FLIGHT);
    this->pRenderFinishedSemaphores = new std::vector<VkSemaphore>(this->MAX_FRAMES_IN_FLIGHT);
    this->pInFlightFences = new std::vector<VkFence>(this->MAX_FRAMES_IN_FLIGHT);
    this->pImagesInFlight = new std::vector<VkFence>(this->pGpuProperties->pSwapchain->getSwapChainImages()->size(), VK_NULL_HANDLE);    

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        if (vkCreateSemaphore(this->getDevice(), &semaphoreInfo, nullptr, &(*this->pImageAvailableSemaphores)[i]) != VK_SUCCESS ||
            vkCreateSemaphore(this->getDevice(), &semaphoreInfo, nullptr, &(*this->pRenderFinishedSemaphores)[i]) != VK_SUCCESS ||
            vkCreateFence(this->getDevice(), &fenceInfo, nullptr, &(*this->pInFlightFences)[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }

}

VkDevice VulkanManager::getDevice()
{
    return this->pComponentsBase->getDevice();
}

VkInstance VulkanManager::getInstance()
{
    return this->pComponentsBase->getInstance();
}

VkSwapchainKHR VulkanManager::getSwapchain()
{
    return this->pCommandBuffers->getSwapchain();
}

VkQueue VulkanManager::getGraphicsQueue()
{
    return this->pComponentsBase->getGraphicsQueue();
}

VkQueue VulkanManager::getPresentQueue()
{
    return this->pComponentsBase->getPresentQueue();
}

const VkCommandBuffer* VulkanManager::getPCommandBuffers(int index)
{   
    return &(*this->pCommandBuffers->pBuffers)[index];
}

const VkImageView* VulkanManager::getPSwapChainImageViews(size_t index)
{
    return &(*this->pSwapChainImageViews)[index];
}

const VkSemaphore* VulkanManager::getPImageAvailableSemaphores(size_t index)
{
    return &(*this->pImageAvailableSemaphores)[index];
}

const VkSemaphore* VulkanManager::getPRenderFinishedSemaphores(size_t index)
{
    return &(*this->pRenderFinishedSemaphores)[index];
}

const VkFence* VulkanManager::getPInFlightFences(size_t index)
{
    return &(*this->pInFlightFences)[index];
}

const VkFence* VulkanManager::getPImagesInFlight(size_t index)
{
    return &(*this->pImagesInFlight)[index];
}

void VulkanManager::setPImagesInFlight(size_t index, const VkFence* valuePointer)
{
    (*this->pImagesInFlight)[index] = *valuePointer;
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

void VulkanManager::recreateSwapChain()
{
    int width = 0;
    int height = 0;

    glfwGetFramebufferSize(this->pComponentsBase->getPWindow(), &width, &height);

    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(this->pComponentsBase->getPWindow(), &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(this->getDevice());

    this->cleanSwapChain();

    this->pGpuProperties->pSwapchain->checkDeviceExtensionSupport(this->pComponentsBase->pPhysicalDevice);
    this->pGpuProperties->pSwapchain->createSwapChain(this->pGpuProperties->pIndices);
    
    this->createImageViews();
    
    this->pRenderPass->createRenderPass(this->pGpuProperties);
    this->pGraphicsPipeline->createGraphicsPipeline(this->pGpuProperties);
    this->pFramebuffers->createFramebuffers(this->pGpuProperties, this->pSwapChainImageViews);

    this->pCommandBuffers = new CommandBuffers(this->pGpuProperties, this->pFramebuffers);
}

void VulkanManager::cleanSwapChain()
{
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        // Wait for fences to complete before destroying them
        /*
            This following line is not from the Vulkan Tutorial, but from the 7-Keeping-your-GPU-fed.pdf
             by the Khronos group.  The tutorial worked fine, except for the following error that kept
             showing up at the sempahore destruction phase.

             Cannot call vkDestroySemaphore on VkSemaphore 0x40fd720000000017[] that is currently in use by a command buffer.
        */
        vkWaitForFences(this->getDevice(), 1, &(*this->pInFlightFences)[i], true, UINT64_MAX);
    }

    for (auto framebuffer : *this->pFramebuffers->pSwapChainFramebuffers)
    {
        vkDestroyFramebuffer(this->getDevice(), framebuffer, nullptr);
    }

    vkFreeCommandBuffers(
        this->getDevice(),
        *this->pComponentsBase->pCommandPool,
        static_cast<uint32_t>(this->pCommandBuffers->pBuffers->size()),
        this->pCommandBuffers->pBuffers->data()
    );

    vkDestroyPipeline(this->getDevice(), *this->pComponentsBase->pGraphicsPipeline, nullptr);
    vkDestroyPipelineLayout(this->getDevice(), *this->pComponentsBase->pPipelineLayout, nullptr);
    vkDestroyRenderPass(this->getDevice(), *this->pComponentsBase->pRenderPass, nullptr);

    for (auto imageView : *this->pSwapChainImageViews)
    {
        vkDestroyImageView(this->pGpuProperties->getDevice(), imageView, nullptr);
    }

    vkDestroySwapchainKHR(this->getDevice(), *this->pComponentsBase->pSwapchain, nullptr);
}

VulkanManager::~VulkanManager()
{
    this->cleanSwapChain();

    vkDestroyBuffer(this->pComponentsBase->getDevice(), *this->pComponentsBase->pVBuffer, nullptr);
    vkFreeMemory(this->pComponentsBase->getDevice(), *this->pComponentsBase->pVBufferMemory, nullptr);

    delete this->pVertexBuffer;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        // Wait for fences to complete before destroying them
        /*
            This following line is not from the Vulkan Tutorial, but from the 7-Keeping-your-GPU-fed.pdf
             by the Khronos group.  The tutorial worked fine, except for the following error that kept
             showing up at the sempahore destruction phase.
        
             Cannot call vkDestroySemaphore on VkSemaphore 0x40fd720000000017[] that is currently in use by a command buffer.
        */
        vkWaitForFences(this->getDevice(), 1, &(*this->pInFlightFences)[i], true, UINT64_MAX);

        vkDestroySemaphore(this->getDevice(), (*this->pRenderFinishedSemaphores)[i], nullptr);
        vkDestroySemaphore(this->getDevice(), (*this->pImageAvailableSemaphores)[i], nullptr);
        vkDestroyFence(this->getDevice(), (*this->pInFlightFences)[i], nullptr);
    }

    vkDestroyCommandPool(this->getDevice(), *this->pComponentsBase->pCommandPool, nullptr);
            
    delete this->pFramebuffers;
    delete this->pGraphicsPipeline;
    delete this->pRenderPass;

    if (enableValidationLayers)
    {
        DestroyDebugUtilsMessengerEXT(*this->pComponentsBase->pInstance, this->debugMessenger, nullptr);
    }

    delete this->pGpuProperties;

    vkDestroySurfaceKHR(*this->pComponentsBase->pInstance, *this->pComponentsBase->pSurface, nullptr);
    vkDestroyInstance(*this->pComponentsBase->pInstance, nullptr);

    delete this->pVulkanLayerProperties;
    delete this->pVulkanExtensionProperties;
    delete this->pGlfwExtensionProperties;    
    delete this->pComponentsBase;
}