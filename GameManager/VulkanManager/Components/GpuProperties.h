#ifndef _GPUPROPERTIES_H_
#define _GPUPROPERTIES_H_

#include <map>
#include <optional>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/QueueFamilyIndices.h"
#include "VulkanManager/Components/LogicalDevice.h"

// GpuProperties Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 60
    The graphics card that we’ll end up selecting will be stored in a VkPhysicalDevice
    handle that is added as a new class member. This object will be implicitly
    destroyed when the VkInstance is destroyed, so we won’t need to do anything
    new in the cleanup function.
*/
class GpuProperties :
    public ComponentsBase
{
public:
    GpuProperties(VkInstance* pInstance, VulkanLayerProperties* pVulkanLayerProperties);
    ~GpuProperties();

    QueueFamilyIndices* pIndices = nullptr;

    void pickPhysicalDevice(VkInstance* pInstance);

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

private:
    LogicalDevice* pLogicalDevice = nullptr;

    std::vector<VkPhysicalDevice>* pDevices = nullptr;
    std::multimap<int, VkPhysicalDevice>* pCandidates = nullptr;

    VkDevice* pDevice = nullptr;
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    int rateDeviceSuitability(VkPhysicalDevice device);
    bool deviceIsSuitable(VkPhysicalDevice device);
};

#endif // _GPUPROPERTIES_H_