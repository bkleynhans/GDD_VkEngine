#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanManager/ComponentsBase.h"

class VertexBuffer :
    public ComponentsBase
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void createVertexBuffer();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

private:
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

#endif // _VERTEXBUFFER_H_