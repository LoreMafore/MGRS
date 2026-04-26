//
// Created by Conrad Mercer on 4/25/2026.
//

#ifndef MGRS_WINDOW_H
#define MGRS_WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include "Global.h"

void config_window(window_config_struct* window_config, uint16_t height, uint16_t width, const char *title, const float color[4]);
void create_window(window_config_struct *window_config);
void resize_window(GLFWwindow *window, int width, int height);
void render_windows(window_config_struct *windows_array[]);

#endif //MGRS_WINDOW_H