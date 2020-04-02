#include "WindowManager.h"

WindowManager::WindowManager(void (*framebufferResizeCallback)(GLFWwindow*, int, int))
{
    this->createWindow(framebufferResizeCallback);
}

void WindowManager::createWindow(void (*framebufferResizeCallback)(GLFWwindow*, int, int))
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    this->pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    glfwSetWindowUserPointer(this->pWindow, this);
    glfwSetFramebufferSizeCallback(this->pWindow, *framebufferResizeCallback);
}

uint32_t WindowManager::getWidth()
{
    return this->WIDTH;
}

uint32_t WindowManager::getHeight()
{
    return this->HEIGHT;
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(this->pWindow);

    glfwTerminate();
}