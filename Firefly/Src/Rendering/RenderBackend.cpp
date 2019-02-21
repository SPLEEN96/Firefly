#include "RenderBackend.h"

#include "PCH_CORE.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Firefly {
namespace Rendering {

std::vector<const char*> extensions;
std::vector<const char*> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
std::vector<const char*> debug_layers      = {"VK_LAYER_LUNARG_standard_validation"};

void RenderBackend::_CreateInstance() {
    VkApplicationInfo app_info  = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app_info.pApplicationName   = "Firefly Rendering Engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "Firefly";
    app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion         = VK_API_VERSION_1_1;

    _QueryRequiredExtensions();

    VkInstanceCreateInfo create_info    = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    create_info.pApplicationInfo        = &app_info;
    create_info.enabledExtensionCount   = static_cast<uint32>(extensions.size());
    create_info.ppEnabledExtensionNames = extensions.data();
    create_info.enabledLayerCount       = static_cast<uint32>(debug_layers.size());
    create_info.ppEnabledLayerNames     = debug_layers.data();

    VK_ASSERT(vkCreateInstance(&create_info, nullptr, &_instance),
              "Failed to create Vulkan Instance.");
}

void RenderBackend::_QueryRequiredExtensions() {
    uint32       ext_count;
    const char** glfw_exts = glfwGetRequiredInstanceExtensions(&ext_count);
    extensions.insert(extensions.end(), glfw_exts, glfw_exts + ext_count);
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}

void RenderBackend::_SetupDebugLayer() {
    VkDebugUtilsMessengerCreateInfoEXT create_info = {
        VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
    create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                              VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                              VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    create_info.pfnUserCallback = DebugCallback;
    create_info.pUserData       = nullptr;

    VK_ASSERT(CreateDebugUtilsMessengerEXT(_instance, &create_info, nullptr,
                                           &_debug_messenger),
              "Failed to Setup Vulkan Debug Messenger");
}

void RenderBackend::_CreateSurface(Window window) {
    VK_ASSERT(glfwCreateWindowSurface(
                  _instance, static_cast<GLFWwindow*>(window.GetPlatformWindow()),
                  nullptr, &_surface),
              "Failed to create Vulkan Surface.");
}

/* === === === === Physical Devices === === === === */
void RenderBackend::_PickPhysicalDevice() {
    uint32 dev_count = 0;
    vkEnumeratePhysicalDevices(_instance, &dev_count, nullptr);
    FFLY_ASSERT(dev_count, "Failed to find GPUs with Vulkan support.");

    VkPhysicalDevice device_list[dev_count];
    vkEnumeratePhysicalDevices(_instance, &dev_count, device_list);

    for (VkPhysicalDevice dev : device_list) {
        if (_IsDeviceSuitable(dev)) {
            _physical_dev = dev;
        }
    }

    FFLY_ASSERT(_physical_dev, "Failed to find a suitable GPU.");

    VkPhysicalDeviceProperties dev_properties = {};
    vkGetPhysicalDeviceProperties(_physical_dev, &dev_properties);
    std::cout << "Device used:" << dev_properties.deviceName << std::endl
              << "API_VERSION:" << dev_properties.apiVersion << std::endl;
}

bool RenderBackend::_IsDeviceSuitable(VkPhysicalDevice dev) {
    VkPhysicalDeviceProperties dev_properties;
    VkPhysicalDeviceFeatures   dev_features;
    vkGetPhysicalDeviceProperties(dev, &dev_properties);
    vkGetPhysicalDeviceFeatures(dev, &dev_features);

    uint32 ext_count;
    vkEnumerateDeviceExtensionProperties(dev, nullptr, &ext_count, nullptr);
    std::vector<VkExtensionProperties> dev_available_ext(ext_count);
    vkEnumerateDeviceExtensionProperties(dev, nullptr, &ext_count,
                                         dev_available_ext.data());

    return true;
}

void RenderBackend::_FindQueueFamilies(VkPhysicalDevice dev, uint32& graphics_index,
                                       uint& presentation_index) {
    graphics_index = presentation_index = -1;

    uint32 queue_family_count;
    vkGetPhysicalDeviceQueueFamilyProperties(_physical_dev, &queue_family_count,
                                             nullptr);
    FFLY_ASSERT(queue_family_count, "Failed to find Queues on Physical Device.");

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(_physical_dev, &queue_family_count,
                                             queue_families.data());

    for (uint32 i = 0; i < queue_families.size(); i++) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphics_index = i;
        }

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(_physical_dev, i, _surface,
                                             &present_support);
        if (present_support) {
            presentation_index = i;
        }

        if (graphics_index != -1 && presentation_index != -1) {
            break;
        }
    }
}

void RenderBackend::_CreateLogicalDevice() {
    uint32 graphics_family_index, present_family_index;
    _FindQueueFamilies(_physical_dev, graphics_family_index, present_family_index);
    std::set<uint32> indices = {graphics_family_index, present_family_index};

    float queue_priority = 1.f;

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    for (auto index : indices) {
        VkDeviceQueueCreateInfo create_info = {
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
        create_info.queueFamilyIndex = index;
        create_info.queueCount       = 1;
        create_info.pQueuePriorities = &queue_priority;
        queue_create_infos.push_back(create_info);
    }

    VkPhysicalDeviceFeatures dev_features = {};
    dev_features.samplerAnisotropy        = VK_TRUE;

    VkDeviceCreateInfo create_info      = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    create_info.queueCreateInfoCount    = static_cast<uint32>(queue_create_infos.size());
    create_info.pQueueCreateInfos       = queue_create_infos.data();
    create_info.pEnabledFeatures        = &dev_features;
    create_info.enabledExtensionCount   = static_cast<uint32>(device_extensions.size());
    create_info.ppEnabledExtensionNames = device_extensions.data();
    create_info.enabledLayerCount       = static_cast<uint32>(debug_layers.size());
    create_info.ppEnabledLayerNames     = debug_layers.data();

    VK_ASSERT(vkCreateDevice(_physical_dev, &create_info, nullptr, &_device),
              "Failed to create Logical Device.");
}
/* ===  ===  === === === === === === */

/* === === === === Swapchain === === === === */
void _CreateSwapChain() {
    VkSwapchainKHR           swapchain;
    VkSwapchainCreateInfoKHR create_info = {VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
}
/* ===  ===  === === === === === === */

/*
 *
 *
 */
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger) {

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
    VkDebugUtilsMessageTypeFlagsEXT             message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data, void* p_user_data) {

    const char* message = p_callback_data->pMessage;
    if (message_severity < VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        FFLY_LOG_CORE_INFO("VULKAN::Validation Layer: {0}", message);
    } else {
        FFLY_LOG_CORE_ERROR("VULKAN::Validation Layer: {0}", message);
    }
    return VK_FALSE;
}

} // namespace Rendering
} // namespace Firefly
