#pragma once
#include "RENDER_CORE.h"

#include "Firefly/Window.h"

namespace Firefly {
namespace Rendering {

class RenderBackend {
  public:
    void Init(Window window) {
        _CreateInstance();
        _SetupDebugLayer();
        _CreateSurface(window);
        _PickPhysicalDevice();
        _CreateLogicalDevice();
    }

    ~RenderBackend() {
        vkDestroyDevice(_device, nullptr);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }

  private:
    void _CreateInstance();
    void _QueryRequiredExtensions();

    void _CreateSurface(Window window);
    /* === Physical Devices === */
    void _PickPhysicalDevice();
    bool _IsDeviceSuitable(VkPhysicalDevice dev); /* TODO */
    void _FindQueueFamilies(VkPhysicalDevice dev, uint32& graphics_index,
                            uint32& presentation_index);
    void _CreateLogicalDevice();
    /* ===  ===  === === === */
    /* === Swapchain === */
    void _CreateSwapchain();
    /* ===  ===  === === === */
    void _CreateImageViews();
    /* === Debug Layer === */
    void _SetupDebugLayer();
    /* ===  ===  === === === */

  private:
    VkInstance               _instance;
    VkSurfaceKHR             _surface;
    VkPhysicalDevice         _physical_dev;
    VkDevice                 _device;
    VkDebugUtilsMessengerEXT _debug_messenger;
};

/* Functions for the debug layer */
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger);
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
    VkDebugUtilsMessageTypeFlagsEXT             message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data, void* p_user_data);

} // namespace Rendering
} // namespace Firefly