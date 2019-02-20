#include "RenderBackend.h"
#include "PCH_CORE.h"

namespace Firefly {
namespace Rendering {

const char* debug_layers[]{"VK_LAYER_LUNARG_standard_validation"};

void RenderBackend::_CreateInstance() {
    VkApplicationInfo app_info  = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app_info.pApplicationName   = "Firefly Rendering Engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "Firefly";
    app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion         = VK_API_VERSION_1_1;

    VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    create_info.pApplicationInfo     = &app_info;
    create_info.enabledLayerCount    = sizeof(debug_layers) / sizeof(char*);
    create_info.ppEnabledLayerNames  = debug_layers;

    VK_ASSERT(vkCreateInstance(&create_info, nullptr, &_instance),
              "Failed to create Vulkan Instance.");
}
} // namespace Rendering
} // namespace Firefly
