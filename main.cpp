#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

// Enables the Nsight Aftermath code instrumentation for GPU crash dump creation.
#define USE_NSIGHT_AFTERMATH 1

#if defined(USE_NSIGHT_AFTERMATH)
#include "DebugManager/NsightAftermathHelpers.h"
#include "DebugManager/NsightAftermathGpuCrashTracker.h"
#include "DebugManager/NsightAftermathShaderDatabase.h"

// Temporary definitions for the NV_device_diagnostics_config extension.
// Remove when the Vulkan SDK has picked up the latest Vulkan headers.
#include "DebugManager/nv_device_diagnostics_config_ext.h"
#endif

#include "GameManager/GameManager.h"

#pragma region CREDITS
/*** 

    Thank you to Alexander Overvoorde for his Vulkan Tutorial from October 2019.  This
    entire framework as well as all comments are taken either directly, or as a variation
    of the information provided in his tutorial.

    For more information related to the tutorial documentation, please refer to the
    source website at:

    https ://vulkan-tutorial.com/

***/
#pragma endregion

int main()
{
    GameManager app;

    try
    {
        app.run();
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}