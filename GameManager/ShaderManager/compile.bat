@ECHO OFF
REM		These two commands tell the compiler to read the GLSL source file and output
REM		a SPIR-V bytecode file using the -o (output) flag.
REM		If your shader contains a syntax error then the compiler will tell you the line
REM		number and problem, as you would expect.
@ECHO ON

C:\VulkanSDK\1.2.131.2\Bin32\glslc.exe shaders_src\shader.vert -o shaders_bin\vert.spv
C:\VulkanSDK\1.2.131.2\Bin32\glslc.exe shaders_src\shader.frag -o shaders_bin\frag.spv
pause