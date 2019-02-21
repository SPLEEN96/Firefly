#pragma once
#include "RENDER_CORE.h"

#include "Firefly/Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Firefly {
namespace Rendering {

class RenderBackend {
  public:
    static RenderBackend& GetInstance() {
        static RenderBackend instance;
        return instance;
    }

    ~RenderBackend() {
        // vkDestroyDevice
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }

    void Init(Window window) {
        _CreateInstance();
        _SetupDebugLayer();
        _CreateSurface(window);
        _PickPhysicalDevice();
        _CreateLogicalDevice();
    }

  private:
    void _CreateInstance();
    void _QueryRequiredExtensions();
    void _SetupDebugLayer();
    void _CreateSurface(Window window);
    /* === Physical Devices === */
    void _PickPhysicalDevice();
    bool _IsDeviceSuitable(VkPhysicalDevice dev); /* TODO */
    void _FindQueueFamilies(VkPhysicalDevice dev, uint32& graphics_index,
                            uint32& presentation_index);
    void _CreateLogicalDevice();
    /* ===  ===  === === === */
    void _CreateSwapChain();
    void _CreateImageViews();

  private:
    VkInstance               _instance;
    VkSurfaceKHR             _surface;
    VkPhysicalDevice         _physical_dev;
    VkDevice                 _device;
    VkDebugUtilsMessengerEXT _debug_messenger;
};

} // namespace Rendering
} // namespace Firefly