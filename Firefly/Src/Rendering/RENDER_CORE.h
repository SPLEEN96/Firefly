#pragma once
#include "FFLY_CORE.h"

#include "vulkan/vulkan.h"

namespace Firefly {
namespace Rendering {

#define VK_ASSERT(x, ...)                                                               \
    {                                                                                   \
        if (x != VK_SUCCESS) {                                                          \
            FFLY_LOG_CORE_CRITICAL(__VA_ARGS__);                                        \
        }                                                                               \
    }

} // namespace Rendering
} // namespace Firefly
