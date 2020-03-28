#ifndef _LOGICALDEVICE_H_
#define _LOGICALDEVICE_H_

#include <set>

#include "VulkanLayerProperties.h"
#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/QueueFamilyIndices.h"
#include "VulkanManager/Components/SwapChain.h"

// Creating a logical device
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 68
    After selecting a physical device to use we need to set up a logical device to
    interface with it. The logical device creation process is similar to the instance
    creation process and describes the features we want to use. We also need to
    specify which queues to create now that we’ve queried which queue families are
    available. You can even create multiple logical devices from the same physical
    device if you have varying requirements.
*/

class LogicalDevice :
    public ComponentsBase
{
public:     
    LogicalDevice(
        VkPhysicalDevice physicalDevice,
        VkDevice* pDevice,
        VulkanLayerProperties* pVulkanLayerProperties,
        QueueFamilyIndices* pIndices,
        SwapChain* pSwapChains
    );
    ~LogicalDevice();

    void specifyQueuesToCreate(QueueFamilyIndices* pIndices);
    void createLogicalDevice(VulkanLayerProperties* pVulkanLayerProperties, SwapChain* pSwapChains);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies;

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkQueue graphicsQueue;
    VkQueue presentQueue;

private:
    VkDeviceCreateInfo createInfo = {};

    float queuePriority = 1.0f;
};

#endif // _LOGICALDEVICE_H_