#ifndef _VERTEX_H_
#define _VERTEX_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#include <iostream>
//#include <stdexcept>
//#include <functional>
//#include <cstdlib>
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <chrono>
#include <array>

class Vertex
{
public:
    Vertex();
    Vertex(glm::vec2 pos, glm::vec3 color);
    ~Vertex();

    static VkVertexInputBindingDescription* getPBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2>* getPAttributeDescriptions();

    glm::vec2 getPos();
    glm::vec3 getColor();

private:
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription* pBindingDescription;
    static std::array<VkVertexInputAttributeDescription, 2>* pAttributeDescriptions;

protected:
    glm::vec2* pPos = &this->pos;
    glm::vec3* pColor = &this->color;

};

#endif // _VERTEX_H_