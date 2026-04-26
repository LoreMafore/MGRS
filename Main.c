//
// Created by Conrad Mercer on 4/13/2026.
//
#include "Main.h"
#include "Colors.h"
#include "KeymapSettings.h"
#include "Window.h"

int main()
{
    initialize_glfw();
    window_config_struct window1;
    window_config_struct window2;

    config_window(&window1, 100, 100, "window1", RED);
    config_window(&window2, 500, 500, "window2", BLUE);

    initialize_glad();

    while(!glfwWindowShouldClose(windows_array[0]->window))
    {
        processInputs(windows_array);
        render_windows(windows_array);
        glfwPollEvents();
    }

    // for (int16_t i; i < amount_of_windows; i++)
    // {
    //     if (windows_array[i] != NULL)
    //     {
    //         free(windows_array[i]);
    //         windows_array[i] = NULL;
    //     }
    // }
    glfwTerminate();
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
