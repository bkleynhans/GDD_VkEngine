#ifndef _GLFWEXTENSIONPROPERTIES_H_
#define _GLFWEXTENSIONPROPERTIES_H_

#include "VulkanManager/SupportedComponents.h"

class GlfwExtensionProperties :
    public SupportedComponents
{
public:
    GlfwExtensionProperties();
    ~GlfwExtensionProperties();

    void addMessageCallback();

    std::vector<const char*> extensions;
    const char** glfwExtensions = nullptr;
    
};

#endif // _GLFWEXTENSIONPROPERTIES_H_