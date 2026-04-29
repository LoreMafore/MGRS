//
// Created by Conrad Mercer on 4/25/2026.
//

#ifndef MGRS_GLOBAL_H
#define MGRS_GLOBAL_H
#include <stdint.h>
#include <GLFW/glfw3.h>

#define TRUE 1
#define FALSE 0


// typedef struct window_config_struct window_config_struct;
typedef struct window_config_struct
{
    uint16_t height;
    uint16_t width;
    const char *title;
    float color[4];
    GLFWwindow *window; // This is set in the creat_window function
    uint8_t debug_bool;
} window_config_struct;

extern window_config_struct **windows_array;
extern uint32_t amount_of_windows;

#endif //MGRS_GLOBAL_H