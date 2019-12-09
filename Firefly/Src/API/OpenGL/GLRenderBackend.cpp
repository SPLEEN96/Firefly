#define FFLY_API_OPENGL
#ifdef FFLY_API_OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rendering/RenderBackend.h"

namespace Firefly {
namespace Rendering {

RenderBackend::RenderBackend() {
}
RenderBackend::~RenderBackend() {
}

RenderBackend* RenderBackend::Create() {
    return new RenderBackend();
}

void RenderBackend::InitAPI() {
    FFLY_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
                "Failed to initialize glad.");

    FFLY_LOG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
    FFLY_LOG_CORE_INFO("GPU: {0}", glGetString(GL_RENDERER));
    FFLY_LOG_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
}

void RenderBackend::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) {
    glViewport(x, y, width, height);
}

void RenderBackend::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void RenderBackend::ClearBuffers(bool color_buffer, bool depth_buffer,
                                 bool stencil_buffer) {
    GLbitfield flags = 0;
    if (color_buffer)
        flags |= GL_COLOR_BUFFER_BIT;
    if (depth_buffer)
        flags |= GL_DEPTH_BUFFER_BIT;
    if (stencil_buffer)
        flags |= GL_STENCIL_BUFFER_BIT;

    glClear(flags);
}

void DrawIndexed();
} // namespace Rendering
}; // namespace Firefly
#endif