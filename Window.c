//
// Created by Conrad Mercer on 4/25/2026.
//

#include "Window.h"
// struct window_config_struct
// {
//     uint16_t height;
//     uint16_t width;
//     const char *title;
//     float color[4];
//     GLFWwindow *window; // This is set in the creat_window function
// };


void config_window(window_config_struct* window_config, uint16_t height, uint16_t width, const char *title, const float color[4], float grid_spacing[2] )
{
    window_config->height = height;
    window_config->width = width;
    window_config->title = title;
    window_config->color[0] = color[0];
    window_config->color[1] = color[1];
    window_config->color[2] = color[2];
    window_config->color[3] = color[3];
    create_window(window_config);
    window_config->grid_spacing_horizontal = grid_spacing[0];
    window_config->grid_spacing_vertical = grid_spacing[1];
}

void create_window(window_config_struct *window_config)
{
    GLFWwindow* window = glfwCreateWindow(window_config->width,window_config->height,window_config->title, NULL, NULL);
    window_config->window = window;

    if (window_config->window == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(window_config->window, window_config);

    amount_of_windows++;
    windows_array = realloc(windows_array, amount_of_windows * sizeof(window_config_struct*));
    windows_array[amount_of_windows - 1] = window_config;

    glfwSetFramebufferSizeCallback(window_config->window, resize_window);
    // glViewport(0, 0,window_config->width,window_config->height);
    glfwMakeContextCurrent(window_config->window);
}

void resize_window(GLFWwindow* window, int width, int height)
{
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);

    window_config_struct *config = glfwGetWindowUserPointer(window);
    if (config == NULL)
    {
        fprintf(stderr, "Failed to resize GLFW window.\n");
        return;
    }
    config->height = height;
    config->width = width;

    set_orthographic_projection(config->grid_data.shader_program, 0.0f, 0.0f, width, height);
    destroy_grid(&config->grid_data);
    config->grid_data = build_grid(config->grid_data.shader_program, width, height, config->grid_spacing_horizontal, config->grid_spacing_vertical);
}

void render_windows(window_config_struct *windows_array[])
{
    for (int i = 0; i < amount_of_windows; i++)
    {
        glfwMakeContextCurrent(windows_array[i]->window);
        glClearColor(windows_array[i]->color[0], windows_array[i]->color[1], windows_array[i]->color[2], windows_array[i]->color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        render_grid(&windows_array[i]->grid_data);
        glfwSwapBuffers(windows_array[i]->window);
    }
}
