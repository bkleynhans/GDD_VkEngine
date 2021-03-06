#include "QueueFamilyIndices.h"

QueueFamilyIndices::QueueFamilyIndices() {}

QueueFamilyIndices::QueueFamilyIndices(VkPhysicalDevice* pPhysicalDevice)
{
    this->findQueueFamilies(pPhysicalDevice);
}

bool QueueFamilyIndices::isComplete()
{
    return this->graphicsFamily.has_value() && presentFamily.has_value();
}

void QueueFamilyIndices::findQueueFamilies(VkPhysicalDevice* pPhysicalDevice)
{
    // Query the number of queue families supported by the device
    vkGetPhysicalDeviceQueueFamilyProperties(*pPhysicalDevice, &this->count, nullptr);

    this->pQueueFamilies = new std::vector<VkQueueFamilyProperties>(this->count);

    // Get data pertaining to the previously discovered queue families
    vkGetPhysicalDeviceQueueFamilyProperties(*pPhysicalDevice, &this->count, this->pQueueFamilies->data());

    int i = 0;

    for (const auto& queueFamily : *this->pQueueFamilies)
    {   // The single & is the bitwise-and operator in c++
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            this->graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(*pPhysicalDevice, i, *pSurface, &presentSupport);

        if (presentSupport)
        {
            this->presentFamily = i;
        }

        if (this->isComplete())
        {
            break;
        }

        i++;
    }
}

QueueFamilyIndices::~QueueFamilyIndices()
{
    // We created with the 'new' keyword so we need to clear memory
    std::vector<VkQueueFamilyProperties>().swap(*this->pQueueFamilies);
}