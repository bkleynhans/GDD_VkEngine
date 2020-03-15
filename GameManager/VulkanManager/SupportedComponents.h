#ifndef _SUPPORTEDCOMPONENTS_H_
#define _SUPPORTEDCOMPONENTS_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>

class SupportedComponents
{
public:
    SupportedComponents();
    ~SupportedComponents();

    uint32_t count = 0;
};

#endif // _SUPPORTEDCOMPONENTS_H_