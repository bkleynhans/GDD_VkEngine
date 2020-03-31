#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

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