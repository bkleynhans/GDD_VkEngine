#ifndef _VULKANEXTENSIONPROPERTIES_H_
#define _VULKANEXTENSIONPROPERTIES_H_

#include "VulkanManager/SupportedComponents.h"

class VulkanExtensionProperties :
    public SupportedComponents
{
public:
    VulkanExtensionProperties();
    ~VulkanExtensionProperties();

    std::vector<VkExtensionProperties>* pExtensions = nullptr;

private:
    void determineExtensionSupport();
};

#endif // _VULKANEXTENSIONPROPERTIES_H_