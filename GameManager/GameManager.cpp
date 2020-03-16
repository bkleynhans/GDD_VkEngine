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
    this->pWindowManager = new WindowManager();
}

void GameManager::initVulkan()
{
    this->pVulkanManager = new VulkanManager();
}

void GameManager::mainLoop()
{
    while (!glfwWindowShouldClose(this->pWindowManager->pWindow))
    {
        glfwPollEvents();
    }
}

void GameManager::cleanup()
{

}

GameManager::~GameManager()
{
    delete this->pVulkanManager;
    delete this->pWindowManager;

    //std::cout << "Game Manager Destroyed" << std::endl;
}