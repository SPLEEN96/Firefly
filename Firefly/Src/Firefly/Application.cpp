#include "Application.h"
#include "PCH_CORE.h"

#include "GLFW/glfw3.h"

namespace Firefly {

Application::Application() {
    m_running = true;
    m_window  = std::unique_ptr<Window>(Window::Create());
    m_window->SetEventCallbackFn(([](const Event& e) {
        return true;
    }));
}
Application::~Application() {
}

void Application::Run() {
    while (IsRunning()) {
        glClearColor(0.24f, 0.23f, 0.31f, 1.0f);
        m_window->OnUpdate();
        glClear(GL_COLOR_BUFFER_BIT);
    }
    m_running = false;
}

bool Application::OnEvent(const Event& e) {
    FFLY_LOG_APP_TRACE("TESTOUILLE");
    return true;
}

Application* CreateApplication() {
}

} // namespace Firefly