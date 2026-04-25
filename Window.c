//
// Created by momer on 4/25/2026.
//

#include "Window.h"

void create_window(int height, int width, const char* window_name)
{
    GLFWwindow* window = glfwCreateWindow(width, height, window_name, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(window);
}
