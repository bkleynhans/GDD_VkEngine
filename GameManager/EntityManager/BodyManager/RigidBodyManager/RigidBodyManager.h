#ifndef _RIGIDBODYMANAGER_H_
#define _RIGIDBODYMANAGER_H_

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

class RigidBodyManager
{
public:
    RigidBodyManager();
    ~RigidBodyManager();

private:

};

#endif // _RIGIDBODYMANAGER_H_