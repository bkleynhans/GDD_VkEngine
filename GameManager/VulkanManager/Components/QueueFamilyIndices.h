#ifndef _QUEUEFAMILYINDICES_H_
#define _QUEUEFAMILYINDICES_H_

#include <optional>

#include "VulkanManager/ComponentsBase.h"

// Queue Family Indices description
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 63
    It has been briefly touched upon before that almost every operation in Vulkan,
    anything from drawing to uploading textures, requires commands to be submit-
    ted to a queue. There are different types of queues that originate from different
    queue families and each family of queues allows only a subset of commands.

    We need to check which queue families are supported by the device and which
    one of these supports the commands that we want to use.
*/
class QueueFamilyIndices :
    public ComponentsBase
{
public:
    QueueFamilyIndices(VkPhysicalDevice* pDevice);
    ~QueueFamilyIndices();

    bool isComplete();

    // Description of std::optional
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 64
        It’s not really possible to use a magic value to indicate the nonexistence of a
        queue family, since any value of uint32_t could in theory be a valid queue family
        index including 0. Luckily C++17 introduced a data structure to distinguish
        between the case of a value existing or not:

        std::optional is a wrapper that contains no value until you assign something
        to it. At any point you can query if it contains a value or not by calling its
        has_value() member function.
    */
    std::optional<uint32_t> graphicsFamily;

private:
    std::vector<VkQueueFamilyProperties>* pQueueFamilies = nullptr;

    void findQueueFamilies(VkPhysicalDevice* pDevice);
};

#endif // _QUEUEFAMILYINDICES_H_