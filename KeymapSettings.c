//
// Created by Conrad Mercer on 4/25/2026.
//

#include "KeymapSettings.h"

void processInputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, TRUE);
    }
}