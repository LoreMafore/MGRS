//
// Created by Conrad Mercer on 4/25/2026.
//

#include "KeymapSettings.h"

void processInputs(window_config_struct *windows_array[])
{
    for (uint16_t i; i < amount_of_windows; i++)
    {
        if (glfwGetKey(windows_array[i]->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(windows_array[i]->window, TRUE);
            // free(windows_array[i]);
            // windows_array[i] = NULL;
        }
    }
}