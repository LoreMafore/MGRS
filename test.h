//
// Created by momer on 4/18/2026.
//

#ifndef MGRS_TEST_H
#define MGRS_TEST_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600


void createWindow(GLFWwindow *window, char window_name[50]);
void createInstance();
void pickPhysicalDevice(); //picks a physical GPU
uint32_t findGraphicsFamily(); //searching for queue family that can use graphics
void createDevice();
void createSwapChain();
void cleaRnup();

#endif //MGRS_TEST_H