#include "Core/Application.h"
#include "PCH_CORE.h"

namespace Firefly {

Application::Application() {
    m_running = true;
    m_window  = std::unique_ptr<Window>(Window::Create("Firefly", 1280, 960));
    m_window->BindEventCallBackFn(FFLY_BIND_EVENT_FN(&Application::OnEvent));

    m_rmodule.Load(*m_window);

    m_imgui_layer = new ImguiLayer(m_window.get());
    this->PushLayer(m_imgui_layer);
}
Application::~Application() {
}

void Application::Run() {
    double frame_time = glfwGetTime();
    double end_frame  = glfwGetTime();
    int    frame      = 0;
    glfwSwapInterval(0);

    while (IsRunning()) {
        frame++;

        m_rmodule.OnUpdate();
        m_imgui_layer->OnUpdate();
        m_window->OnUpdate();

        if (end_frame - frame_time >= 1) {
            frame_time = glfwGetTime();
            std::cout << "CORE_ENGINE:" << frame << "FPS" << std::endl;
            frame = 0;
        }
        end_frame = glfwGetTime();
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