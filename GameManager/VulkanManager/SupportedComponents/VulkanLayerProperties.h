#ifndef _VULKANLAYERPROPERTIES_H_
#define _VULKANLAYERPROPERTIES_H_

#include "VulkanManager/SupportedComponents.h"

class VulkanLayerProperties :
    public SupportedComponents
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