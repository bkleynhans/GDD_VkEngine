#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"

class IndexBuffer :
    public ComponentsBase
{
public:
    IndexBuffer();
    ~IndexBuffer();

private:

};

#endif // _INDEXBUFFER_H_