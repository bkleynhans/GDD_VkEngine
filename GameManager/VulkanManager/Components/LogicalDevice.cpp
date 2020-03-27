#include "LogicalDevice.h"

LogicalDevice::LogicalDevice(
    VkPhysicalDevice physicalDevice, VkDevice* pDevice,
    VulkanLayerProperties* pVulkanLayerProperties,
    QueueFamilyIndices* pIndices)
{    
    this->specifyQueuesToCreate(pIndices);
    this->createLogicalDevice(pVulkanLayerProperties);
    
    if (vkCreateDevice(physicalDevice, &this->createInfo, nullptr, pDevice) != VK_SUCCESS)    
    {
        throw std::runtime_error("failed to create logical device!");
    }

    // Getting a handle to the graphics queue
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 71
        The queues are automatically created along with the logical device, but we don’t
        have a handle to interface with them yet.

        We can use the vkGetDeviceQueue function to retrieve queue handles for each
        queue family. The parameters are the logical device, queue family, queue index
        and a pointer to the variable to store the queue handle in. Because we’re only
        creating a single queue from this family, we’ll simply use index 0.
    */
    vkGetDeviceQueue(*pDevice, pIndices->graphicsFamily.value(), 0, &this->graphicsQueue);
    vkGetDeviceQueue(*pDevice, pIndices->presentFamily.value(), 0, &this->presentQueue);
}

// Specify which queues to create
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 68
    The creation of a logical device involves specifying a bunch of details in structs
    again, of which the first one will be VkDeviceQueueCreateInfo. This structure
    describes the number of queues we want for a single queue family. Right now
    we’re only interested in a queue with graphics capabilities.
*/
void LogicalDevice::specifyQueuesToCreate(QueueFamilyIndices* pIndices)
{
    uniqueQueueFamilies = { pIndices->graphicsFamily.value(), pIndices->presentFamily.value() };

    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};

        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.pNext = NULL;
        queueCreateInfo.queueFamilyIndex = pIndices->graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &this->queuePriority;

        this->queueCreateInfos.push_back(queueCreateInfo);
    }    
}

// Specify which queues to create
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 68
    Start filling in the main VkDeviceCreateInfo structure.
*/
void LogicalDevice::createLogicalDevice(VulkanLayerProperties* pVulkanLayerProperties)
{
    this->createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    this->createInfo.pNext = NULL;
    this->createInfo.flags = 0;
    this->createInfo.pQueueCreateInfos = this->queueCreateInfos.data();
    this->createInfo.queueCreateInfoCount = static_cast<uint32_t>(this->queueCreateInfos.size());

    this->createInfo.pEnabledFeatures = &this->deviceFeatures;

    this->createInfo.enabledExtensionCount = 0;

    if (enableValidationLayers)
    {
        this->createInfo.enabledLayerCount = static_cast<uint32_t>(pVulkanLayerProperties->validationLayers.size());
        this->createInfo.ppEnabledLayerNames = pVulkanLayerProperties->validationLayers.data();
    }
    else
    {
        this->createInfo.enabledLayerCount = 0;
    }
}

LogicalDevice::~LogicalDevice()
{

}