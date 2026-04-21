//
// Created by Conrad Mercer on 4/13/2026.
//
#include "test.h"

int main()
{
    char test_window_name[50] = "Test";
    GLFWwindow *window = NULL;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphics_queue;
    VkSwapchainKHR swap_chain;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = createWindow(window, test_window_name);
    createInstance(&instance);

    if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create window surface\n");
        return 1;
    }

    pickPhysicalDevice(instance, &physical_device);
    createDevice(physical_device, &device, &graphics_queue);
    createSwapChain(surface, physical_device, device, &graphics_queue);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    cleanup(instance, window, surface, device, &swap_chain);
    return 0;
}
