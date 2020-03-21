#ifndef _GPUPROPERTIES_H_
#define _GPUPROPERTIES_H_

#include <map>
#include <optional>

#include "VulkanManager/SupportedComponents.h"

// We will be using multiple queues for operations, therefore it is
// better to contain them in a struct
struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    
    bool isComplete()
    {
        return graphicsFamily.has_value();

    }
};

// GpuProperties Description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 60
    The graphics card that we’ll end up selecting will be stored in a VkPhysicalDevice
    handle that is added as a new class member. This object will be implicitly
    destroyed when the VkInstance is destroyed, so we won’t need to do anything
    new in the cleanup function.
*/
class GpuProperties :
    public SupportedComponents
{
public:
    GpuProperties(VkInstance* pInstance);
    ~GpuProperties();

    void pickPhysicalDevice(VkInstance* pInstance);

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;    

private:
    std::vector<VkPhysicalDevice>* pDevices = nullptr;
    std::multimap<int, VkPhysicalDevice>* pCandidates = nullptr;

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    //bool isDeviceSuitable(VkPhysicalDevice device);
    int rateDeviceSuitability(VkPhysicalDevice device);
    bool deviceIsSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

#endif // _GPUPROPERTIES_H_