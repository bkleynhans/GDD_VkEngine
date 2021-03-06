#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

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

#include "EntityManager/BodyManager/BodyManager.h"

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    BodyManager* getPBodyManager();

private:    
    BodyManager* pBodyManager = nullptr;
};

#endif // _ENTITYMANAGER_H_