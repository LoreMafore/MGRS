//
// Created by Conrad Mercer on 4/13/2026.
//
#include "Main.h"

#include "Window.h"

int main()
{
    initialize_glfw();
    initialize_glad();
    return 0;
}

void initialize_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
}

void initialize_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to load GLAD\n");
        exit(EXIT_FAILURE);
    }
}
