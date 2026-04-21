//
// Created by Conrad Mercer on 4/18/2026.
//

#include "test.h"

GLFWwindow* createWindow(GLFWwindow *window, char window_name[50])
{
    window = glfwCreateWindow(WIDTH, HEIGHT, window_name, NULL, NULL);
    return window;
}

void createInstance(VkInstance *instance)
{
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Test",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    uint32_t ext_count = 0;
    const char **ext_names = glfwGetRequiredInstanceExtensions(&ext_count);

    const VkInstanceCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = ext_count,
        .ppEnabledExtensionNames = ext_names,
    };

    if (vkCreateInstance(&info, NULL, instance) != VK_SUCCESS)
    {
        fprintf(stderr, "failed to create vulkan instance\n");
        exit(1);
    }
}

void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physical_device)
{
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(instance, &count, NULL); //gets the amount of devices
    VkPhysicalDevice *devices = malloc(count * (sizeof(VkPhysicalDevice)));  //allocate space for devices, like GPUs
    vkEnumeratePhysicalDevices(instance, &count, devices); //maps devices to allocate memory
    *physical_device = devices[0];
    free(devices);
}

uint32_t findGraphicsFamily(VkPhysicalDevice physical_device)
{
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, NULL);
    VkQueueFamilyProperties *props = malloc(count * (sizeof(VkQueueFamilyProperties)));
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, props);

    for (uint32_t queue_family = 0; queue_family < count; queue_family++)
    {
        if (props[queue_family].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            free(props);
            uint32_t graphic_queue = queue_family;
            return graphic_queue;
        }
    }
    free(props);
    fprintf(stderr, "No graphics queue found\n");
    exit(1);
}

void createDevice(VkPhysicalDevice physical_device, VkDevice *device, VkQueue *graphics_queue)
{
    uint32_t queue_family = findGraphicsFamily(physical_device);
    float priority = 1.0f;

    VkDeviceQueueCreateInfo queue_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queue_family,
        .queueCount = 1,
        .pQueuePriorities = &priority,
    };

    const char *device_extensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    const VkDeviceCreateInfo info =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queue_info,
        .enabledExtensionCount = 1,
        .ppEnabledExtensionNames = device_extensions,
    };

    if (vkCreateDevice(physical_device, &info, NULL, device) != VK_SUCCESS)
    {
        fprintf(stderr, "failed to create logical device\n");
        exit(1);
    }
    vkGetDeviceQueue(*device, queue_family, 0, graphics_queue);
}

void createSwapChain(VkSurfaceKHR surface, VkPhysicalDevice physical_device, VkDevice device, VkSwapchainKHR *swap_chain)
{
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &capabilities);

    const VkSwapchainCreateInfoKHR info =
    {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = capabilities.minImageCount +1,
        .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,
        .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
        .imageExtent = capabilities.currentExtent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR,
        .clipped = VK_TRUE,
        .preTransform = capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
    };

    if (vkCreateSwapchainKHR(device, &info, NULL, swap_chain) != VK_SUCCESS)
    {
        fprintf(stderr, "failed to create swap chain\n");
        exit(1);
    }
}

void cleanup(VkInstance instance, GLFWwindow* window, VkSurfaceKHR surface, VkDevice device, VkSwapchainKHR swap_chain)
{
    vkDestroySwapchainKHR(device,swap_chain, NULL);
    vkDestroyDevice(device, NULL);
    vkDestroySurfaceKHR(instance,surface, NULL);
    vkDestroyInstance(instance, NULL);
    glfwDestroyWindow(window);
    glfwTerminate();
}
