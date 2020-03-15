#include "GameManager.h"

GameManager::GameManager()
{

}

void GameManager::run()
{    
    //initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void GameManager::initVulkan()
{

}

void GameManager::mainLoop()
{
    while (!glfwWindowShouldClose(windowManager.window))
    {
        glfwPollEvents();
    }
}

void GameManager::cleanup()
{

}

GameManager::~GameManager()
{

}