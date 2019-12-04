#include "Core/Application.h"
#include "PCH_CORE.h"

namespace Firefly {

Application::Application() {
    m_running = true;
    m_window  = std::unique_ptr<Window>(Window::Create("Firefly", 1280, 960));
    m_window->BindEventCallBackFn(FFLY_BIND_EVENT_FN(&Application::OnEvent));

    m_rmodule.Load(*m_window);

    m_imgui_layer = new ImguiLayer(m_window.get());
    this->PushOverlay(m_imgui_layer);
}
Application::~Application() {
}

void Application::Run() {
    while (IsRunning()) {
        m_rmodule.OnUpdate();

        /* Update each Layers */
        for (std::vector<Layer*>::iterator it = m_layer_stack.Begin();
             it != m_layer_stack.End(); it++) {
            (*it)->OnUpdate();
        }

        /* If a Layer has a UI, Draw it */
        m_imgui_layer->Begin();
        for (std::vector<Layer*>::iterator it = m_layer_stack.Begin();
             it != m_layer_stack.End(); it++) {
            (*it)->OnImGuiDraw();
        }
        m_imgui_layer->End();

        m_window->OnUpdate();
    }
    m_running = false;
}

bool Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(
        FFLY_BIND_EVENT_FN(&Application::OnWindowCloseEvent));
}

void Application::PushLayer(Layer* layer) {
    m_layer_stack.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer) {
    m_layer_stack.PushOverlay(layer);
}

bool Application::OnWindowCloseEvent(WindowCloseEvent& e) {
    m_running = false;
    return true;
}

} // namespace Firefly