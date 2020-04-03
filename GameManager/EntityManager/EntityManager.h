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

//#include "WindowManager/WindowManager.h"
//#include "VulkanManager/ComponentsBase.h"
//#include "VulkanManager/Components/GlfwExtensionProperties.h"
//#include "VulkanManager/Components/VulkanExtensionProperties.h"
//#include "VulkanManager/Components/VulkanLayerProperties.h"
//#include "VulkanManager/Components/GpuProperties.h"
//#include "VulkanManager/Components/RenderPass.h"
//#include "VulkanManager/Components/GraphicsPipeline.h"
//#include "VulkanManager/Components/Framebuffers.h"
//#include "VulkanManager/Components/CommandBuffers.h"
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