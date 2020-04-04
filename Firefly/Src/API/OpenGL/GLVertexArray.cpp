#define FFLY_API_OPENGL
#ifdef FFLY_API_OPENGL
#include <glad/glad.h>
#include "Rendering/VertexArray.h"

namespace Firefly {
namespace Rendering {
void VertexArray::Bind() const {
    glBindVertexArray(m_handle);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vbo) {
    this->Bind();
    vbo.Bind();

    m_vbos.push_back(vbo);
    this->Unbind();
}

void VertexArray::SetIndexBuffer(const IndexBuffer& ibo) {
    this->Bind();
    //ibo.Bind();

    m_ibo = ibo;
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