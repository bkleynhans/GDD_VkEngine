#include "WindowManager.h"

WindowManager::WindowManager()
{
    this->createWindow();
}

void WindowManager::createWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    std::cout << "Window Manager Created" << std::endl;
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(this->pWindow);

    glfwTerminate();

    std::cout << "Window Manager Destroyed" << std::endl;
}