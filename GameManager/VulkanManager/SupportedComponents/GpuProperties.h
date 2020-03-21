#ifndef _GPUPROPERTIES_H_
#define _GPUPROPERTIES_H_

#include <map>

#include "VulkanManager/SupportedComponents.h"

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
};

#endif // _GPUPROPERTIES_H_