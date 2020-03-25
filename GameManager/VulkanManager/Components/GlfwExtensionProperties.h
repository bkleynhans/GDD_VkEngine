#ifndef _GLFWEXTENSIONPROPERTIES_H_
#define _GLFWEXTENSIONPROPERTIES_H_

#include "VulkanManager/ComponentsBase.h"

class GlfwExtensionProperties :
    public ComponentsBase
{
public:
    GlfwExtensionProperties();
    ~GlfwExtensionProperties();

    void addMessageCallback();

    std::vector<const char*> pExtensions;
    const char** glfwExtensions = nullptr;

};

#endif // _GLFWEXTENSIONPROPERTIES_H_