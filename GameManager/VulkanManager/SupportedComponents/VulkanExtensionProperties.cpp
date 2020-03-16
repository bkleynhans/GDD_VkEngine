#include "VulkanExtensionProperties.h"

VulkanExtensionProperties::VulkanExtensionProperties()
{
    this->determineExtensionSupport();
}

void VulkanExtensionProperties::determineExtensionSupport()
{
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 47
        If you look at the vkCreateInstance documentation then you'll see that one
        of the possible error codes is VK_ERROR_EXTENSION_NOT_SUPPORTED. To retrieve
        a list of supported extensions becore creating an instance, there's the
        vkEnumerateInstanceExtensionProperties function.  It takes a pointer to a
        variable that stores the number of extensions and an array of
        VkExtensionProperties to store details of the extensions.
    */
    vkEnumerateInstanceExtensionProperties(nullptr, &this->count, nullptr);

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 47
        Now allocate an array to hold the extension details
    */
    this->pExtensions = new std::vector<VkExtensionProperties>(this->count);

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 47
        Now we can query the extension details
    */
    vkEnumerateInstanceExtensionProperties(nullptr, &this->count, this->pExtensions->data());

    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        We can list the supported extensions with a for-loop to display some
        details about Vulkan support
    */
    std::cout << std::endl;
    std::cout << "Native Supported Extensions : " << std::endl;
    for (const auto& extension : *this->pExtensions)
    {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
    std::cout << std::endl;
}

VulkanExtensionProperties::~VulkanExtensionProperties()
{
    // We created with the 'new' keyword so we need to clear memory
    std::vector<VkExtensionProperties>().swap(*this->pExtensions);

    //std::cout << "Vulkan Extension Properties Destroyed" << std::endl;
}
