#ifndef _UNIFORMBUFFEROBJECT_H_
#define _UNIFORMBUFFEROBJECT_H_

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

class UniformBufferObject
{
public:
    UniformBufferObject();
    ~UniformBufferObject();

private:
    alignas(16) glm::mat4* pModel = nullptr;
    alignas(16) glm::mat4* pView = nullptr;
    alignas(16) glm::mat4* pProj = nullptr;
};

#endif // _UNIFORMBUFFEROBJECT_H_