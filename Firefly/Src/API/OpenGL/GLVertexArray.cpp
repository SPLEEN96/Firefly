#define FFLY_API_OPENGL
#ifdef FFLY_API_OPENGL
#include <glad/glad.h>
#include "Rendering/VertexArray.h"
#include "Rendering/Buffer.h"

namespace Firefly {
namespace Rendering {
void VertexArray::Bind() const {
    glBindVertexArray(m_handle);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vbuffer) {
    FFLY_ASSERT(vbuffer.GetLayout().Size(),
                "VertexArray::AddVertexBuffer() : vbuffer buffer has no layout");
    this->Bind();
    vbuffer.Bind();

    m_vbuffers.push_back(vbuffer);
    this->Unbind();
}

void VertexArray::SetIndexBuffer(const IndexBuffer& ibuffer) {
    this->Bind();
    // ibuffer.Bind();

    m_ibuffer = ibuffer;
    this->Unbind();
}
} // namespace Rendering

namespace Factory {
namespace VertexArray {
Rendering::VertexArray* Create() {
    uint32 vao_handle;
    glGenVertexArrays(1, &vao_handle);

    Rendering::VertexArray* vao = new Rendering::VertexArray();
    vao->SetAPIHandle(vao_handle);
    return vao;
}
} // namespace VertexArray
} // namespace Factory
} // namespace Firefly
#endif