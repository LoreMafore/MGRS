//
// Created by Conrad Mercer on 4/25/2026.
//

#include "Window.h"

GLFWwindow* create_window(int height, int width, const char* window_name)
{
    GLFWwindow* window = glfwCreateWindow(width, height, window_name, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, resize_window);
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(window);

    return window;
}

void resize_window(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
