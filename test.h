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


GLFWwindow* createWindow(GLFWwindow* window, char window_name[50]);
void createInstance(VkInstance *instance);
void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physical_device); //picks a physical GPU
uint32_t findGraphicsFamily(VkPhysicalDevice physical_device); //searching for queue family that can use graphics
void createDevice(VkPhysicalDevice physical_device, VkDevice *device, VkQueue *graphics_queue);
void createSwapChain(VkSurfaceKHR surface, VkPhysicalDevice physical_device, VkDevice device, VkSwapchainKHR *swap_chain);
void cleanup(VkInstance instance, GLFWwindow *window, VkSurfaceKHR surface, VkDevice device, VkSwapchainKHR swap_chain);

#endif //MGRS_TEST_H