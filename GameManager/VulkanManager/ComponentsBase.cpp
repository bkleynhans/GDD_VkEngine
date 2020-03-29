#include "ComponentsBase.h"

VkDevice* ComponentsBase::pDevice = nullptr;
//VkPhysicalDevice* ComponentsBase::pPhysicalDevice = nullptr;

ComponentsBase::ComponentsBase()
{
    
}

VkDevice ComponentsBase::getDevice()
{
    return *pDevice;
}

//VkPhysicalDevice ComponentsBase::getPhysicalDevice()
//{
//    return *this->pPhysicalDevice;
//}

ComponentsBase::~ComponentsBase()
{

}