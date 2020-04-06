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
void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}
void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/* === Index Buffer === */
void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}
void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace VertexBuffer {
Rendering::VertexBuffer* Create(float* vertices, const uint32& size,
                                std::vector<Rendering::VertexAttribute> attributes) {
    uint32                           buffer_handle = 0;
    Rendering::AttributesDescription buffer_layout(attributes);

    glGenBuffers(1, &buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);

    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    for (uint32 i = 0; i < buffer_layout.Size(); i++) {
        glEnableVertexAttribArray(i);
        auto count  = buffer_layout[i].GetCount();
        auto type   = Rendering::VertexAttributeToOpenGLType(buffer_layout[i].Type);
        auto stride = buffer_layout.Stride;
        auto offset = buffer_layout[i].Offset;

        glVertexAttribPointer(
            i, buffer_layout[i].GetCount(),
            Rendering::VertexAttributeToOpenGLType(buffer_layout[i].Type),
            buffer_layout[i].ToNormalize, buffer_layout.Stride,
            (void*)buffer_layout[i].Offset);
    }

    Rendering::VertexBuffer* buffer = new Rendering::VertexBuffer();
    buffer->SetAPIHandleAndLayout(buffer_handle, buffer_layout);

    return buffer;
}
} // namespace VertexBuffer

namespace IndexBuffer {
Rendering::IndexBuffer* Create(const uint32* indices, const uint32& count) {
    GLuint handle;
    glGenBuffers(1, &handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices,
                 GL_STATIC_DRAW);

    Rendering::IndexBuffer* ibuffer = new Rendering::IndexBuffer();
    ibuffer->SetAPIHandleAndCount(handle, count);

    return ibuffer;
}
} // namespace IndexBuffer
} // namespace Factory

} // namespace Firefly
#endif