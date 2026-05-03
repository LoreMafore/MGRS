//
// Created by Conrad Mercer on 4/13/2026.
//
#include "Main.h"
#include "Colors.h"
#include "KeymapSettings.h"
#include "Window.h"
#include "shaders.h"

int main()
{
    initialize_glfw();
    window_config_struct window1 = {0};
    window_config_struct window2 = {0};

    uint16_t win_h1 = 100;
    uint16_t win_w1 = 100;
    uint16_t win_h2 = 500;
    uint16_t win_w2 = 500;

    config_window(&window1, win_h1, win_w1, "window1", RED);
    config_window(&window2, win_h2, win_w2, "window2", BLUE);

    initialize_glad();

    //win 1
    uint32_t grid_program_1 = create_shader_program(
        "shader/GridShader.vert",
      "shader/GridShader.frag"
        );

    glfwMakeContextCurrent(windows_array[0]->window);
     glViewport(0, 0,windows_array[0]->width,windows_array[0]->height);
    set_orthographic_projection(grid_program_1, 0.0f, 0.0f, win_h1, win_w1);
    windows_array[0]->grid_data = build_grid(grid_program_1, win_h1, win_w1, 5.0f, 5.0f);

    //win 2
    uint32_t grid_program_2 = create_shader_program(
        "shader/GridShader.vert",
      "shader/GridShader.frag"
        );

    glfwMakeContextCurrent(windows_array[1]->window);
    glViewport(0, 0,windows_array[0]->width,windows_array[0]->height);
    set_orthographic_projection(grid_program_2, 0.0f, 0.0f, win_h2, win_w2);
    windows_array[1]->grid_data = build_grid(grid_program_2, win_h2, win_w2, 5.0f, 5.0f);

    while(!glfwWindowShouldClose(windows_array[0]->window) &&
          !glfwWindowShouldClose(windows_array[1]->window))
    {
        processInputs(windows_array);
        render_windows(windows_array);
        glfwPollEvents();
    }

    for (int16_t i; i < amount_of_windows; i++)
    {
        destroy_grid(&windows_array[i]->grid_data);

        // if (windows_array[i] != NULL)
        // {
        //     free(windows_array[i]);
        //     windows_array[i] = NULL;
        // }
    }

    glDeleteProgram(grid_program_1);
    glDeleteProgram(grid_program_2);
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
