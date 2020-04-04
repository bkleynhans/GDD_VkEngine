#ifndef _SQUARE_H_
#define _SQUARE_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <array>

#include "RigidBodyManager.h"
#include "EntityManager/BodyManager/Vertex.h"

class Square :
    public RigidBodyManager
{
public:
    Square();
    ~Square();

    const std::vector<Vertex>* getPVertices();
    const std::vector<uint16_t>* getPIndices();

private:
    // This variable contains the vec2 vertex, and the vec3 color
    // for each vertex
    const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };

    // Indices of the vertices as defined in the vertices variable above
    // this variable
    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

    const std::vector<Vertex>* pVertices = &vertices;
    const std::vector<uint16_t>* pIndices = &indices;
};

#endif // _SQUARE_H_