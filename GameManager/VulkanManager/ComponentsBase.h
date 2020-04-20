#ifndef _COMPONENTSBASE_H_
#define _COMPONENTSBASE_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>

#include "WindowManager/WindowManager.h"
#include "EntityManager/EntityManager.h"
#include "EntityManager/BodyManager/BodyManager.h"

struct UniformBufferObject
{
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class ComponentsBase
{
public:
    ComponentsBase();
    ~ComponentsBase();

    VkDevice getDevice();
    VkInstance getInstance();
    VkSwapchainKHR getSwapchain();
    VkPhysicalDevice getPhysicalDevice();
    VkQueue getGraphicsQueue();
    VkQueue getPresentQueue();

    std::vector<VkImage>* getSwapChainImages();

    void setPWindowManager(WindowManager* pWindow);
    GLFWwindow* getPWindow();
    
    void setPEntityManager(EntityManager* pEntity);
    
    static VkInstance* pInstance;
    static VkSurfaceKHR* pSurface;

    static VkPhysicalDevice* pPhysicalDevice;
    static VkDevice* pDevice;

    static VkQueue* pGraphicsQueue;
    static VkQueue* pPresentQueue;
    
    static VkSwapchainKHR* pSwapchain;
    
    static VkRenderPass* pRenderPass;
    static VkDescriptorSetLayout* pDescriptorSetLayout;
    static VkPipelineLayout* pPipelineLayout;
    static VkPipeline* pGraphicsPipeline;

    static VkCommandPool* pCommandPool;

    static VkBuffer* pVBuffer;
    static VkDeviceMemory* pVBufferMemory;    
    static VkBuffer* pIndexBuffer;
    static VkDeviceMemory* pIndexBufferMemory;

    static VkDescriptorPool* pDescriptorPool;
    static std::vector<VkDescriptorSet>* pDescriptorSets;

    static std::vector<VkImage>* pSwapChainImages;
    static std::vector<VkBuffer>* pUniformBuffers;
    static std::vector<VkDeviceMemory>* pUniformBuffersMemory;

    uint32_t count = 0;    
        
// STRUCT for Validation Layers
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 50
    Add two configuration variables to the program to specify the layers
    to enable and whether to enable them or not. I’ve chosen to base that value
    on whether the program is being compiled in debug mode or not. The NDEBUG
    macro is part of the C++ standard and means “not debug”.
*/
#ifdef NDEBUG
    static const bool enableValidationLayers = false;
#else
    static const bool enableValidationLayers = true;
#endif
  
protected:
    static WindowManager* pWindowManager;
    static EntityManager* pEntityManager;
    static BodyManager* pBodyManager;

};

#endif // _COMPONENTSBASE_H_