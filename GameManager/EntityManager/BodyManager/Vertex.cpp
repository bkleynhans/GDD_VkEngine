#include "Vertex.h"

VkVertexInputBindingDescription* Vertex::pBindingDescription = nullptr;
std::array<VkVertexInputAttributeDescription, 2>* Vertex::pAttributeDescriptions = nullptr;

Vertex::Vertex()
{
    this->pos = { 0.0f, 0.0f };
    this->color = { 0.0f, 0.0f, 0.0f };
}

Vertex::Vertex(glm::vec2 pos, glm::vec3 color)
{
    this->pos = pos;
    this->color = color;
}

glm::vec2 Vertex::getPos()
{
    return this->pos;
}

glm::vec3 Vertex::getColor()
{
    return this->color;
}

VkVertexInputBindingDescription* Vertex::getPBindingDescription()
{
    pBindingDescription = new VkVertexInputBindingDescription;

    pBindingDescription->binding = 0;
    pBindingDescription->stride = sizeof(Vertex);
    pBindingDescription->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return pBindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2>* Vertex::getPAttributeDescriptions()
{
    pAttributeDescriptions = new std::array<VkVertexInputAttributeDescription, 2>;

    (*pAttributeDescriptions)[0].binding = 0;
    (*pAttributeDescriptions)[0].location = 0;
    (*pAttributeDescriptions)[0].format = VK_FORMAT_R32G32_SFLOAT;
    (*pAttributeDescriptions)[0].offset = offsetof(Vertex, pos);

    (*pAttributeDescriptions)[1].binding = 0;
    (*pAttributeDescriptions)[1].location = 1;
    (*pAttributeDescriptions)[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    (*pAttributeDescriptions)[1].offset = offsetof(Vertex, color);

    return pAttributeDescriptions;
}

Vertex::~Vertex()
{
    delete pBindingDescription;
    delete pAttributeDescriptions;
}