#include "VulkanLayerProperties.h"

VulkanLayerProperties::VulkanLayerProperties()
{
    this->determineValidationLayerSupport();
}

void VulkanLayerProperties::determineValidationLayerSupport()
{
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 51
        List all of the available layers using the vkEnumerateInstanceLayerProperties
        function.  Its usage is identical to that of
        vkEnumerateInstanceExtensionProperties used above.
    */
    vkEnumerateInstanceLayerProperties(&this->count, nullptr);

    this->pAvailableLayers = new std::vector<VkLayerProperties>(this->count);

    vkEnumerateInstanceLayerProperties(&this->count, this->pAvailableLayers->data());
}

// Validation Layers
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
    The Vulkan API is designed around the idea of minimal driver overhead and one
    of the manifestations of that goal is that there is very limited error checking in
    the API by default. Even mistakes as simple as setting enumerations to incorrect
    values or passing null pointers to required parameters are generally not explicitly
    handled and will simply result in crashes or undefined behavior. Because Vulkan
    requires you to be very explicit about everything you’re doing, it’s easy to make
    many small mistakes like using a new GPU feature and forgetting to request it
    at logical device creation time.

    However, that doesn’t mean that these checks can’t be added to the API. Vulkan
    introduces an elegant system for this known as validation layers. Validation
    layers are optional components that hook into Vulkan function calls to apply
    additional operations.
*/
bool VulkanLayerProperties::checkValidationLayerSupport()
{
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 51
        Check if all of the layers in validationLayers exist in the
        availableLayers list.
    */
    for (const char* layerName : this->validationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : *this->pAvailableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

VulkanLayerProperties::~VulkanLayerProperties()
{
    // We created with the 'new' keyword so we need to clear memory
    std::vector<VkLayerProperties>().swap(*this->pAvailableLayers);
}