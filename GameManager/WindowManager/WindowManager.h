#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

// Window Manager Description
/*
    
*/

class WindowManager
{
public:
    WindowManager();    
    ~WindowManager();

    void createWindow();
    uint32_t getWidth();
    uint32_t getHeight();    

    GLFWwindow* pWindow = nullptr;

private:    

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
};

#endif // _WINDOWMANAGER_H_