//
// Created by Conrad Mercer on 4/13/2026.
//
#include "CoreVulkanUtilis.h"
#include "Main.h"
uint8_t framebufferResized = FALSE;

int main()
{
    char test_window_name[50] = "Test";
    GLFWwindow *window = NULL;
    VkInstance instance;
    VkDebugUtilsMessengerEXT *debug_messenger = VK_NULL_HANDLE;
    // VkSurfaceKHR surface;
    // VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    // VkDevice device;
    // VkQueue graphics_queue;
    // VkSwapchainKHR swap_chain;
    // VkClearColorValue background_color = {{255.0f, 255.0f, 255.0f}};

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = createWindow(test_window_name);
    // glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    createInstance(&instance, test_window_name);

    // pickPhysicalDevice(instance, &physical_device);
    // createDevice(physical_device, &device, &graphics_queue);
    // createSwapChain(window, surface, physical_device, device, &swap_chain);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (framebufferResized)
        {
            // recreateSwapChain(window, surface, physical_device, device, &swap_chain);
            // framebufferResized = FALSE;
            // printf("Swapchain Recreated Successfully\n");
        }
    }

    // vkDeviceWaitIdle(device);
    // cleanup(instance, window, surface, device, swap_chain);
    cleanup(instance, window);
    return 0;
}

void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    framebufferResized = TRUE;
}
