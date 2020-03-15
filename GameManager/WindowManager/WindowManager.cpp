#include "WindowManager.h"

WindowManager::WindowManager()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
    this->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(this->window);

    glfwTerminate();
}