#include "GraphicsPipeline.h"

GraphicsPipeline::GraphicsPipeline(GpuProperties* pGpuProperties)
{
    this->createGraphicsPipeline(pGpuProperties);
}

// Load the bytecode of the two shaders
void GraphicsPipeline::createGraphicsPipeline(GpuProperties* pGpuProperties)
{
    auto vertShaderCode = this->readFile("GameManager/ShaderManager/shaders_bin/vert.spv");
    auto fragShaderCode = this->readFile("GameManager/ShaderManager/shaders_bin/frag.spv");

// SHADER STAGE CREATION

    // Creating the shader modules
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 105-106
        Shader modules are just a thin wrapper around the shader bytecode that we’ve
        previously loaded from a file and the functions defined in it. The compilation
        and linking of the SPIR-V bytecode to machine code for execution by the GPU
        doesn’t happen until the graphics pipeline is created. That means that we’re allowed
        to destroy the shader modules again as soon as pipeline creation is finished,
        which is why we’ll make them local variables in the createGraphicsPipeline
        function instead of class members
    */
    VkShaderModule vertShaderModule = this->createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = this->createShaderModule(fragShaderCode);

    // Assign shaders to pipeline stage
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 106
        To actually use the shaders we’ll need to assign them to a specific pipeline stage
        through VkPipelineShaderStageCreateInfo structures as part of the actual
        pipeline creation process.
    */
    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    // Define an array with the structs
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 106
        Define an array that contains these two structs, which we’ll later
        use to reference them in the actual pipeline creation step.
    */
    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

// END SHADER STAGE CREATION
// VERTEX INPUT
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 108
        The VkPipelineVertexInputStateCreateInfo structure describes the format
        of the vertex data that will be passed to the vertex shader. It describes this in
        roughly two ways:

            • Bindings: spacing between data and whether the data is per-vertex or
                per-instance (see instancing)
            • Attribute descriptions: type of the attributes passed to the vertex shader,
                which binding to load them from and at which offset
    */
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr;
// END VERTEX INPUT
// INPUT ASSEMBLY
   /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 109
        The VkPipelineInputAssemblyStateCreateInfo struct describes two things:
        what kind of geometry will be drawn from the vertices and if primitive restart
        should be enabled. The former is specified in the topology member and can
        have values like:

            • VK_PRIMITIVE_TOPOLOGY_POINT_LIST: points from vertices
            • VK_PRIMITIVE_TOPOLOGY_LINE_LIST: line from every 2 vertices without
                reuse
            • VK_PRIMITIVE_TOPOLOGY_LINE_STRIP: the end vertex of every line is used
                as start vertex for the next line
            • VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST: triangle from every 3 vertices
                without reuse
            • VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP: the second and third vertex
                of every triangle are used as first two vertices of the next triangle

        Normally, the vertices are loaded from the vertex buffer by index in sequential
        order, but with an element buffer you can specify the indices to use yourself.
        This allows you to perform optimizations like reusing vertices. If you set the
        primitiveRestartEnable member to VK_TRUE, then it’s possible to break up
        lines and triangles in the _STRIP topology modes by using a special index of
        0xFFFF or 0xFFFFFFFF.
    */
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;
// END INPUT ASSEMBLY
// VIEW PORTS AND SCISSORS
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 109-111
        viewport basically describes the region of the framebuffer that the output will
        be rendered to. This will almost always be (0, 0) to (width, height)
    */
    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)pGpuProperties->pSwapChain->getSwapChainExtent().width;
    viewport.height = (float)pGpuProperties->pSwapChain->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = pGpuProperties->pSwapChain->getSwapChainExtent();

    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;
// END VIEW PORTS AND SCISSORS
// RASTERIZER
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 112
        The rasterizer takes the geometry that is shaped by the vertices from the
        vertex shader and turns it into fragments to be colored by the fragment
        shader. It also performs depth testing, face culling and the scissor test,
        and it can be configured to output fragments that fill entire polygons
        or just the edges (wireframe rendering). All this is configured using the
        VkPipelineRasterizationStateCreateInfo structure.
    */
    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f;
    rasterizer.depthBiasClamp = 0.0f;
    rasterizer.depthBiasSlopeFactor = 0.0f;
// END RASTERIZER
// MULTISAMPLING
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 112
        The VkPipelineMultisampleStateCreateInfo struct configures multisampling,
        which is one of the ways to perform anti-aliasing. It works by combining
        the fragment shader results of multiple polygons that rasterize to the same
        pixel. This mainly occurs along edges, which is also where the most noticeable
        aliasing artifacts occur. Because it doesn’t need to run the fragment shader
        multiple times if only one polygon maps to a pixel, it is significantly less
        expensive than simply rendering to a higher resolution and then downscaling.
        Enabling it requires enabling a GPU feature.
    */
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;
// END MULTISAMPLING
// COLOR BLENDING
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 113
        After a fragment shader has returned a color, it needs to be combined with the
        color that is already in the framebuffer. This transformation is known as color
        blending and there are two ways to do it:

            • Mix the old and new value to produce a final color
            • Combine the old and new value using a bitwise operation

        There are two types of structs to configure color blending. The first struct,
        VkPipelineColorBlendAttachmentState contains the configuration per attached
        framebuffer and the second struct, VkPipelineColorBlendStateCreateInfo
        contains the global color blending settings.
    */
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;
// END COLOR BLENDING
// PIPELINE LAYOUT
    /* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 115
        You can use uniform values in shaders, which are globals similar to dynamic
        state variables that can be changed at drawing time to alter the behavior of
        your shaders without having to recreate them. They are commonly used to pass
        the transformation matrix to the vertex shader, or to create texture samplers
        in the fragment shader.
        
        These uniform values need to be specified during pipeline creation by creating a
        VkPipelineLayout object. Even though we won’t be using them until a future
        chapter, we are still required to create an empty pipeline layout.
    */
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
// END PIPELINE LAYOUT

    pPipelineLayout = new VkPipelineLayout;

    if (vkCreatePipelineLayout(*pDevice, &pipelineLayoutInfo, nullptr, pPipelineLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }


    vkDestroyShaderModule(*pDevice, fragShaderModule, nullptr);
    vkDestroyShaderModule(*pDevice, vertShaderModule, nullptr);
}

// Create the shader modules
/* Vulkan Tutorial - Alexander Overvoorde - October 2019 - page 105
    Refer to description in calling module under "Creating the shader modules"
*/
VkShaderModule GraphicsPipeline::createShaderModule(const std::vector<char>& code)
{
    VkShaderModuleCreateInfo createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;

    if (vkCreateShaderModule(*pDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
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
    // We created with the 'new' keyword so we need to clear memory
    delete pPipelineLayout;
}
