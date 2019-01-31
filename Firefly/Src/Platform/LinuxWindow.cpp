#include "LinuxWindow.h"

namespace Firefly {

Window* Window::Create(const WinAttributes& attributes) {
    return new LinuxWindow(attributes);
}

LinuxWindow::LinuxWindow(const WinAttributes& attributes) {
    m_data.Title  = attributes.Title;
    m_data.Width  = attributes.Width;
    m_data.Height = attributes.Height;

    this->Initialize();
    this->InitGLFWCallbacks();
}

LinuxWindow::~LinuxWindow() {
    glfwDestroyWindow(m_window);
}

void LinuxWindow::Initialize() {
    FFLY_ASSERT(glfwInit(), "Failed to init GLFW");

    m_window = glfwCreateWindow(m_data.Width, m_data.Height,
                                m_data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    FFLY_LOG_CORE_INFO("Created Window {0} ({1}, {2})", m_data.Title,
                       m_data.Width, m_data.Height);

    glfwSetWindowUserPointer(m_window, &m_data);
}

void LinuxWindow::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

} // namespace Firefly