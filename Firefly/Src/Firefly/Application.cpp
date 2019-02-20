#include "Application.h"
#include "PCH_CORE.h"

#include "glad/glad.h"

namespace Firefly {

Application::Application() {
    m_running = true;
    m_window  = std::unique_ptr<Window>(Window::Create("Firefly", 1280, 720));
    m_window->SetEventCallbackFn(([](Event& e) {
        // FFLY_LOG_CORE_TRACE("{0}", e.ToString());
        // EventDispatcher test(e);
        // test.Dispatch(E_KEY_PRESSED,testouille);
        // m_gui->OnEvent(e);
        return true;
    }));
    m_window->BindEventCallBackFn(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    m_gui = new GUI();
}
Application::~Application() {
}

void Application::Run() {
    while (IsRunning()) {
        glClearColor(0.24f, 0.23f, 0.31f, 1.0f);
        m_gui->OnUpdate(m_window->Data().Width, m_window->Data().Height);
        m_window->OnUpdate();
        glClear(GL_COLOR_BUFFER_BIT);
    }
    m_running = false;
}

bool Application::OnEvent(Event& e) {
    m_gui->OnEvent(e);
}

Application* CreateApplication() {
}


} // namespace Firefly