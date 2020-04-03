#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

#include "WindowManager/WindowManager.h"
#include "VulkanManager/VulkanManager.h"
#include "EntityManager/EntityManager.h"

class GameManager
{
public:
    GameManager();    
    ~GameManager();

    void run();

    static void framebufferResizeCallback(GLFWwindow* pWindow, int width, int height);

private:
    WindowManager* pWindowManager = nullptr;
    VulkanManager* pVulkanManager = nullptr;
    EntityManager* pEntityManager = nullptr;

    static bool framebufferResized;
    
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void drawFrame();
};

#endif // _GAMEMANAGER_H_