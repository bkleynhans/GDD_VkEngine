#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    this->createVertexBuffer();
}

void VertexBuffer::createVertexBuffer()
{
    VkBufferCreateInfo bufferInfo = {};

    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(pBodyManager->getPSquare()->getPVertices()[0]) * pBodyManager->getPSquare()->getPVertices()->size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    pVBuffer = new VkBuffer();

    if (vkCreateBuffer(*pDevice, &bufferInfo, nullptr, pVBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(*pDevice, *pVBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = this->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    pVBufferMemory = new VkDeviceMemory();

    if (vkAllocateMemory(*pDevice, &allocInfo, nullptr, pVBufferMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(*pDevice, *pVBuffer, *pVBufferMemory, 0);

    void* data;
    vkMapMemory(*pDevice, *pVBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, pBodyManager->getPSquare()->getPVertices()->data(), (size_t)bufferInfo.size);
    vkUnmapMemory(*pDevice, *pVBufferMemory);
}

uint32_t VertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(*pPhysicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }
}

VertexBuffer::~VertexBuffer()
{

}