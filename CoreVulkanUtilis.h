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


GLFWwindow* createWindow(char window_name[50]);
void createInstance(VkInstance *instance, char app_name_array[50]);
void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physical_device); //picks a physical GPU
uint32_t findGraphicsFamily(VkPhysicalDevice physical_device); //searching for queue family that can use graphics
void createDevice(VkPhysicalDevice physical_device, VkDevice *device, VkQueue *graphics_queue);
void createSwapChain(GLFWwindow *window, VkSurfaceKHR surface, VkPhysicalDevice physical_device, VkDevice device, VkSwapchainKHR *swap_chain);
void cleanupSwapChain(VkDevice device, VkSwapchainKHR swap_chain);
void recreateSwapChain(GLFWwindow *window, VkSurfaceKHR surface, VkPhysicalDevice physical_device, VkDevice device, VkSwapchainKHR *swap_chain);
// void cleanup(VkInstance instance, GLFWwindow *window, VkSurfaceKHR surface, VkDevice device, VkSwapchainKHR swap_chain);

void createDebugCallBack(VkInstance *instance, VkDebugUtilsMessengerEXT *debug_messenger);

void cleanup(VkInstance instance, GLFWwindow *window);



#endif //MGRS_TEST_H