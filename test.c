//
// Created by Conrad Mercer on 4/18/2026.
//

#include "test.h"

GLFWwindow        *window;
VkInstance        instance;
VkSurfaceKHR      surface;
VkPhysicalDevice  physDev = VK_NULL_HANDLE;
VkDevice          device;
VkQueue           graphicsQueue;
VkSwapchainKHR    swapchain;
