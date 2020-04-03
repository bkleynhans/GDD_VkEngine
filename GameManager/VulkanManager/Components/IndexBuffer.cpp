#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
    pIndexBuffer = new VkBuffer();
    pIndexBufferMemory = new VkDeviceMemory();

    this->createIndexBuffer();
}

void IndexBuffer::createIndexBuffer()
{

}

IndexBuffer::~IndexBuffer()
{
    delete pIndexBufferMemory;
    delete pIndexBuffer;    
}