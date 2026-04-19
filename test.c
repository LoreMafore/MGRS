//
// Created by Conrad Mercer on 4/18/2026.
//

#include "test.h"

char test_window_name[50] = "Test";
GLFWwindow        *window;
VkInstance        instance;
VkSurfaceKHR      surface;
VkPhysicalDevice  physical_device = VK_NULL_HANDLE;
VkDevice          device;
VkQueue           graphics_queue;
VkSwapchainKHR    swap_chain;

void createWindow(GLFWwindow *window, char window_name[50] )
{
    window = glfwCreateWindow(WIDTH, HEIGHT, window_name, NULL, NULL);
}

void createInstance()
{
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Test",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    uint32_t ext_count = 0;
    const char **ext_names = glfwGetRequiredInstanceExtensions(&ext_count);

    VkInstanceCreateInfo ci = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = ext_count,
        .ppEnabledExtensionNames = ext_names,
    };

    if (vkCreateInstance(&ci, NULL, &instance) != VK_SUCCESS)
    {
        fprintf(stderr, "failed to create vulkan instance\n");
        exit(1);
    }
}

void pickPhysicalDevice()
{
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(instance, &count, NULL); //gets the amount of devices
    VkPhysicalDevice *devices = malloc(count * (sizeof(VkPhysicalDevice)));  //allocate space for devices, like GPUs
    vkEnumeratePhysicalDeviceGroups(instance, &count, devices); //maps devices to allocate memory
    physical_device = devices[0];
    free(devices);
}

uint32_t findGraphicsFamily()
{
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, NULL);
    VkQueueFamilyProperties *props = malloc(count * (sizeof(props)));
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, props);

    for (uint32_t i = 0; i < count; i++)
    {
        if (props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            free(props);
        }
    }
}

void createDevice()
{
}
