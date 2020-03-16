#include "GlfwExtensionProperties.h"

GlfwExtensionProperties::GlfwExtensionProperties()
{
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 46
        Because Vulkan is a platform agnostic API, we need to specify the desired
        global extensions in order to interface with the window system.  GLFW has
        a handy built-in function that returns the extension(s) it needs to do that
        which we can pass to the struct.
    */
    this->glfwExtensions = glfwGetRequiredInstanceExtensions(&count);

    // Create a list of extensions
    std::vector<const char*>(this->glfwExtensions, this->glfwExtensions + this->count).swap(this->extensions);
}

// Message Callback
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 53
    The extensions specified by GLFW are always required, but the debug
    messenger extension is conditionally added. Note that I’ve used the
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME macro here which is equal to the
    literal string “VK_EXT_debug_utils”. Using this macro lets you avoid typos.
*/
void GlfwExtensionProperties::addMessageCallback()
{
    // Add the VK_EXT_DEBUG_UTILS_EXTENSION_NAME extension if enableValidationLayers is true
    this->extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}

GlfwExtensionProperties::~GlfwExtensionProperties()
{
    // We created with the 'new' keyword so we need to clear memory
    std::vector<const char*>().swap(this->extensions);

    //std::cout << "GLFW Extension Properties Destroyed" << std::endl;
}
