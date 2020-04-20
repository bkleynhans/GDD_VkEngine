#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include "VulkanManager/ComponentsBase.h"
#include "VulkanManager/Components/GpuProperties.h"

class VertexBuffer :
    public ComponentsBase
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void updateUniformBuffer(GpuProperties* pGpuProperties, uint32_t currentImage);

private:
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

#endif // _VERTEXBUFFER_H_