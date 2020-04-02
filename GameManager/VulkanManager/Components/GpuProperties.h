#ifndef _GPUPROPERTIES_H_
#define _GPUPROPERTIES_H_

#include <map>
#include <optional>

#include "WindowManager/WindowManager.h"
#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/QueueFamilyIndices.h"
#include "VulkanManager/Components/LogicalDevice.h"
#include "VulkanManager/Components/Swapchain.h"

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
    GpuProperties(
        VulkanLayerProperties* pVulkanLayerProperties
    );
    ~GpuProperties();

    QueueFamilyIndices* pIndices = nullptr;
    Swapchain* pSwapchain = nullptr;

    void pickPhysicalDevice(VkSurfaceKHR* pSurface);
    void cleanupSwapChain();

private:
    LogicalDevice* pLogicalDevice = nullptr;

    std::vector<VkPhysicalDevice>* pDevices = nullptr;
    std::multimap<int, VkPhysicalDevice>* pCandidates = nullptr;

    VkPhysicalDevice* pCandidate;
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    int rateDeviceSuitability(VkPhysicalDevice candidate);
    bool deviceIsSuitable(VkPhysicalDevice* pCandidate);
};

#endif // _GPUPROPERTIES_H_