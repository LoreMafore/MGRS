//
// Created by Conrad Mercer on 4/25/2026.
//

#ifndef MGRS_WINDOW_H
#define MGRS_WINDOW_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    int height;
    int width;
    const char* title;
    float color[4];


} window_config_struct;

GLFWwindow* create_window(int height, int width, const char* window_name);
void resize_window(GLFWwindow *window, int width, int height);

#endif //MGRS_WINDOW_H