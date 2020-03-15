#include "GameManager.h"

GameManager::GameManager()
{

}

void GameManager::run()
{    
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void GameManager::initWindow()
{
    this->windowManager = new WindowManager();
}

void GameManager::initVulkan()
{
    this->vulkanManager = new VulkanManager();
}

void GameManager::mainLoop()
{
    while (!glfwWindowShouldClose(this->windowManager->window))
    {
        glfwPollEvents();
    }
}

void GameManager::cleanup()
{

}

GameManager::~GameManager()
{
    delete this->vulkanManager;
    delete this->windowManager;

    std::cout << "Game Manager Destroyed" << std::endl;
}