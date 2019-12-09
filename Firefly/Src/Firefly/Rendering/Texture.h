#pragma once
#include "FFLY_CORE.h"

namespace Firefly {
namespace Rendering {
class Texture {
  public:
    Texture() {}
    ~Texture();

    // void BindToFramebuffer(Framebuffer* target);

	void Bind();

    void SetHandleAPI(uint32 handle) {
        if (!initialized) {
            m_handle    = handle;
            initialized = true;
        }
    }

  private:
    uint32 m_handle;
    bool   initialized = false;
};
} // namespace Rendering

namespace Factory {
namespace Texture {
Rendering::Texture* Create(const char* filename, bool repeat);
} // namespace Texture
} // namespace Factory

} // namespace Firefly