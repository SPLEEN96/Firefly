#pragma once
#include "FFLY_CORE.h"
#include "Rendering/Buffer.h"

namespace Firefly {
namespace Rendering {
class VertexArray {
  public:
    VertexArray() {}
    ~VertexArray() {}

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(const VertexBuffer& vbo);
    void SetIndexBuffer(const IndexBuffer& ibo);

    void SetAPIHandle(const uint32& handle) {
        if (!initialized) {
            m_handle    = handle;
            initialized = true;
        }
    }

  private:
    uint32                    m_handle = 0;
    std::vector<VertexBuffer> m_vbuffers;
    IndexBuffer               m_ibuffer;
	
    bool                      initialized = false;
};
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace VertexArray {
Rendering::VertexArray* Create();
}
} // namespace Factory
} // namespace Firefly