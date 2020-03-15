#ifndef _WINDOWMANGER_H_
#define _WINDOWMANGER_H_

#include <GLFW/glfw3.h>

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    GLFWwindow* window;

private:
    const int WIDTH = 800;
    const int HEIGHT = 600;
};

#endif // _WINDOWMANAGER_H_