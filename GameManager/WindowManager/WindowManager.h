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
    void createWindow();
    ~WindowManager();

    GLFWwindow* pWindow = nullptr;

private:    

    const int WIDTH = 800;
    const int HEIGHT = 600;
};

#endif // _WINDOWMANAGER_H_