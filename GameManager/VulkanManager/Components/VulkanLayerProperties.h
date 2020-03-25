#ifndef _VULKANLAYERPROPERTIES_H_
#define _VULKANLAYERPROPERTIES_H_

#include "VulkanManager/ComponentsBase.h"

class VulkanLayerProperties :
    public ComponentsBase
{
public:
    VulkanLayerProperties();
    ~VulkanLayerProperties();

    bool checkValidationLayerSupport();

    std::vector<VkLayerProperties>* pAvailableLayers = nullptr;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

private:
    void determineValidationLayerSupport();
};

#endif // _VULKANLAYERPROPERTIES_H_