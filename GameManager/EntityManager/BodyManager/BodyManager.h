#ifndef _BODYMANAGER_H_
#define _BODYMANAGER_H_

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

#include "EntityManager/BodyManager/RigidBodyBase/Square.h"

class BodyManager
{
public:
    BodyManager();
    ~BodyManager();

    Square* getPSquare();

private:
    Square* pSquare = nullptr;

};

#endif // _BODYMANAGER_H_