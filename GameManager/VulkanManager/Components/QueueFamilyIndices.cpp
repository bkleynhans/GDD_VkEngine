#include "QueueFamilyIndices.h"

QueueFamilyIndices::QueueFamilyIndices(VkPhysicalDevice* pDevice)
{
    this->findQueueFamilies(pDevice);
}

bool QueueFamilyIndices::isComplete()
{
    return this->graphicsFamily.has_value();
}

void QueueFamilyIndices::findQueueFamilies(VkPhysicalDevice* pDevice)
{
    // Query the number of queue families supported by the device
    vkGetPhysicalDeviceQueueFamilyProperties(*pDevice, &this->count, nullptr);

    pQueueFamilies = new std::vector<VkQueueFamilyProperties>(this->count);

    // Get data pertaining to the previously discovered queue families
    vkGetPhysicalDeviceQueueFamilyProperties(*pDevice, &this->count, this->pQueueFamilies->data());

    int i = 0;

    for (const auto& queueFamily : *this->pQueueFamilies)
    {   // The single & is the bitwise-and operator in c++
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            this->graphicsFamily = i;
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