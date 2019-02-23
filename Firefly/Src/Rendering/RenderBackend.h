#pragma once
#include "Rendering/PresentationObjects.h"
#include "Rendering/RENDER_CORE.h"

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
        _CreateSwapchain(window);
        _CreateRenderPass();
        _CreatePresentationObjects();
    }

    void OnUpdate();

    ~RenderBackend() { _CleanUp(); }

  private:
    void _CreateInstance();
    void _QueryRequiredExtensions();

    void _CreateSurface(Window window);
    /* === Physical Devices === */
    void _PickPhysicalDevice();
    bool _IsDeviceSuitable(VkPhysicalDevice dev); /* TODO */
    void _FindQueueFamilies(VkPhysicalDevice dev, uint32* graphics_index,
                            uint32* presentation_index);
    void _CreateLogicalDevice();
    /* ===  ===  === === === */
    /* === Swapchain === */
    void _CreateSwapchain(Window window);
    void _ChooseSwapchainSurfaceFormat(std::vector<VkSurfaceFormatKHR>& format);
    void _ChooseSwapchainPresentMode(std::vector<VkPresentModeKHR>& present_mode);
    void _QuerySwapchainSupport(VkSurfaceCapabilitiesKHR*        available_capabilities,
                                std::vector<VkSurfaceFormatKHR>* available_formats,
                                std::vector<VkPresentModeKHR>* available_present_modes);
    /* ===  ===  === === === */
    /* === Pipeline === */
    void _CreateRenderPass();
    /* ===  ===  === === === */
    /* === Presentation === */
    void _CreatePresentationObjects();
    /* ===  ===  === === === */
    /* === Debug Layer === */
    void _SetupDebugLayer();
    /* ===  ===  === === === */
    void _CleanUp();

  private:
    VkInstance   _instance;
    VkSurfaceKHR _surface;
    /* ===  ===  === === === === === === */
    VkPhysicalDevice _physical_dev;
    VkDevice         _device;
    VkQueue          _graphics_queue;
    VkQueue          _present_queue;
    /* ===  ===  === === === === === === */
    VkSwapchainKHR           _swapchain;
    std::vector<VkImage>     _swapchain_images;
    std::vector<VkImageView> _swapchain_image_views;
    VkFormat                 _swapchain_img_format;
    VkExtent2D               _swapchain_extent;
    /* ===  ===  === === === === === === */
    std::vector<Presentation::FramebufferAttachment> _color_attachments;
    Presentation::FramebufferAttachment              _depth_attachment;
    std::vector<Presentation::Framebuffer>           swapchain_framebuffers;
    /* ===  ===  === === === === === === */
    std::vector<VkRenderPass> _renderpass;
    /* ===  ===  === === === === === === */
    VkCommandPool _command_pool;
    /* ===  ===  === === === === === === */
    /* ===  ===  === === === === === === */
    VkDebugUtilsMessengerEXT _debug_messenger;
};

/* Functions for the debug layer */

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
    VkDebugUtilsMessageTypeFlagsEXT             message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data, void* p_user_data);
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance                   instance,
                                   VkDebugUtilsMessengerEXT     messenger,
                                   const VkAllocationCallbacks* pAllocator);

} // namespace Rendering
} // namespace Firefly