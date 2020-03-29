#include "GraphicsPipeline.h"

GraphicsPipeline::GraphicsPipeline()
{

}

void GraphicsPipeline::createGraphicsPipeline()
{
    auto vertShaderCode = this->readFile("ShaderManager/shaders_bin/vert.spv");
    auto fragShaderCode = this->readFile("ShaderManager/shaders_bin/frag.spv");


}

VkShaderModule GraphicsPipeline::createShaderModule(const std::vector<char>& code)
{
    VkShaderModuleCreateInfo createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;

    return nullptr;
    
}

// Read a shader file
std::vector<char> GraphicsPipeline::readFile(const std::string& filename)
{
    // Read file from the end, and as binary
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 104
        The readFile function will read all of the bytes from the specified file and
        return them in a byte array managed by std::vector.
        
        We start by opening the file with two flags:
        • ate: Start reading at the end of the file
        • binary: Read the file as binary file (avoid text transformations)

        The advantage of starting to read at the end of the file is that we can use the
        read position to determine the size of the file and allocate a buffer
    */
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    // Seek to beginning of file and real all bytes at once
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    // Close the file
    file.close();

    return buffer;
}

GraphicsPipeline::~GraphicsPipeline()
{

}
