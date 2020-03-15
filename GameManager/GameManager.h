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

class GameManager
{
public:

    GameManager();
    void run();
    ~GameManager();

private:
    WindowManager* windowManager = nullptr;
    VulkanManager* vulkanManager = nullptr;
    
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    /*void initWindow()
    {

    }

    void initVulkan()
    {

    }

    void mainLoop()
    {
        
    }

    void cleanup()
    {

    }*/
};

#endif // _GAMEMANAGER_H_