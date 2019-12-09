#define FFLY_API_OPENGL
#ifdef FFLY_API_OPENGL
#include <glad/glad.h>
#include "Rendering/Buffer.h"
#include "PCH_CORE.h"

namespace Firefly {
namespace Rendering {

GLenum VertexAttributeToOpenGLType(VertexAttribute::AttrType attr_type) {
    switch (attr_type) {
    case VertexAttribute::AttrType::FLOAT:
        return GL_FLOAT;
    case VertexAttribute::AttrType::FLOAT2:
        return GL_FLOAT;
    case VertexAttribute::AttrType::FLOAT3:
        return GL_FLOAT;
    case VertexAttribute::AttrType::FLOAT4:
        return GL_FLOAT;
    default:
        return 0;
    }
}

/* === Vertex Buffer === */
VertexBuffer* VertexBuffer::Create(float* vertices, uint32 size,
                                   std::vector<VertexAttribute> attributes) {
}

VertexBuffer::VertexBuffer(float* vertices, uint32 size,
                           std::vector<VertexAttribute> attributes)
    : m_layout(attributes) {
    glGenBuffers(1, &m_handle);
    this->Bind();

    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    for (uint32 i = 0; i < m_layout.Size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, m_layout[i].GetCount(), VertexAttributeToOpenGLType(m_layout[i].Type),
            m_layout[i].ToNormalize, m_layout.Stride, (void*)m_layout[i].Offset);
    }
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}
void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/* === Index Buffer === */

IndexBuffer* IndexBuffer::Create(uint32 indices, uint32 size) {
}

} // namespace Rendering
} // namespace Firefly
#endif