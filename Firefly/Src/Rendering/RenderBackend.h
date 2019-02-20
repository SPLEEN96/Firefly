#pragma once
#include "RENDER_CORE.h"

#include "Firefly/Window.h"

namespace Firefly {
namespace Rendering {

class RenderBackend {
  public:
    static RenderBackend GetInstance() {
        static RenderBackend instance;
        return instance;
    }

    ~RenderBackend() { vkDestroyInstance(_instance, nullptr); }

    void Init(Window window) {
        _CreateInstance();
        // _SetupDebugLayer();
        // _CreateSurface();
        // _EnumeratePhysicalDevices();
        // _PickPhysicalDevice();
    }

  private:
    void _CreateInstance();
    void _SetupDebugLayer();
    void _CreateSurface();
    void _EnumeratePhysicalDevices();
    void _PickPhysicalDevice();

  private:
    VkInstance _instance;
};

} // namespace Rendering
} // namespace Firefly