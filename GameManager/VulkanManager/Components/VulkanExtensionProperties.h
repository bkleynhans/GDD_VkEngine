#ifndef _VULKANEXTENSIONPROPERTIES_H_
#define _VULKANEXTENSIONPROPERTIES_H_

#include "VulkanManager/ComponentsBase.h"

class VulkanExtensionProperties :
    public ComponentsBase
{
public:
    VulkanExtensionProperties();
    ~VulkanExtensionProperties();

    std::vector<VkExtensionProperties>* pExtensions = nullptr;

private:
    void determineExtensionSupport();
};

#endif // _VULKANEXTENSIONPROPERTIES_H_