//
// Created by Conrad Mercer on 4/18/2026.
//

#include "CoreVulkanUtilis.h"
#include "VulkanErrorMacro.h"

GLFWwindow* createWindow( char window_name[50])
{
    return glfwCreateWindow(WIDTH, HEIGHT, window_name, NULL, NULL);
}

void createInstance(VkInstance *instance, char app_name_array[50])
{
    const char *layers_array[] = {"VK_LAYER_KHRONOS_validation"};
    uint32_t amount_of_layers = sizeof(layers_array) / sizeof(layers_array[0]);

    const char *extensions_array[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_KHR_win32_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME
    };
    uint32_t amount_of_extensions = sizeof(extensions_array) / sizeof(extensions_array[0]);

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = app_name_array,
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    const VkInstanceCreateInfo instance_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = amount_of_layers,
        .ppEnabledLayerNames = layers_array,
        .enabledExtensionCount = amount_of_extensions,
        .ppEnabledExtensionNames = extensions_array,
    };

    if (vkCreateInstance(&instance_info, NULL, instance) != VK_SUCCESS)
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

void createSwapChain(GLFWwindow *window, VkSurfaceKHR surface, VkPhysicalDevice physical_device, VkDevice device, VkSwapchainKHR *swap_chain)
{
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &capabilities);

    uint32_t width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    VkExtent2D extent = {width, height};

    const VkSwapchainCreateInfoKHR info =
    {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = capabilities.minImageCount + 1,
        .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,
        .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
        .imageExtent = extent,
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

void cleanupSwapChain(VkDevice device, VkSwapchainKHR swap_chain)
{
    vkDestroySwapchainKHR(device, swap_chain, NULL);
}

void recreateSwapChain(GLFWwindow* window, VkSurfaceKHR surface, VkPhysicalDevice physical_device, VkDevice device,
    VkSwapchainKHR* swap_chain)
{
    uint32_t width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(device);
    vkDestroySwapchainKHR(device, *swap_chain, NULL);
    createSwapChain(window, surface, physical_device, device, swap_chain);
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
    void *user_data
    )
{
    printf("Debug callback: %s\n", callback_data->pMessage);
    printf("    Severity: %s\n", GetDebugSeverityStr(severity));
    printf("    Type: %s\n", GetDebugType(message_type));
    printf("    Objects ");

    for (uint32_t i = 0; i < callback_data->objectCount; i++)
    {
        printf("%llx ", callback_data->pObjects[i].objectHandle);
    }

    return VK_FALSE;
}

void createDebugCallBack(VkInstance *instance, VkDebugUtilsMessengerEXT *debug_messenger)
{
    VkDebugUtilsMessengerCreateInfoEXT messenger_create_info =
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext = NULL,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = &debugCallback,
        .pUserData = NULL
    };

    PFN_vkCreateDebugUtilsMessengerEXT vk_create_debug_utils_messenger_ext = VK_NULL_HANDLE;
    vk_create_debug_utils_messenger_ext = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vk_create_debug_utils_messenger_ext");
    if (!vk_create_debug_utils_messenger_ext)
    {
        fprintf(stderr, "Can't find address of vl_create_debug");
        exit(1);
    }

    VkResult result = vkCreateDebugUtilsMessengerEXT(instance, &messenger_create_info, NULL, &debug_messenger);
    CHECK_VK_RESULT(result, "debug callback failed");

}

// void cleanup(VkInstance instance, GLFWwindow* window, VkSurfaceKHR surface, VkDevice device, VkSwapchainKHR swap_chain)
void cleanup(VkInstance instance, GLFWwindow* window)
{
    if (instance != NULL)
    {
        vkDestroyInstance(instance, NULL);
        printf("Instance destroyed\n");
    }
    // vkDestroySwapchainKHR(device,swap_chain, NULL);
    // vkDestroyDevice(device, NULL);
    // vkDestroySurfaceKHR(instance,surface, NULL);
    glfwDestroyWindow(window);
    printf("Window destroyed\n");
    glfwTerminate();
}
