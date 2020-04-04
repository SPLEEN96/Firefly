/* NOTES
-Make Create() functions Friend of Class??
*/
#pragma once
#include "FFLY_CORE.h"

#include "Core/Window.h"

#include "Core/LayerStack.h"
#include "Imgui/ImguiLayer.h"

#include "Rendering/RenderModule.h"

namespace Firefly {

class Application {
  public:
    Application();
    virtual ~Application();

    void Run();
    bool OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    const bool& IsRunning() const { return m_running; }

  private:
    bool OnWindowCloseEvent(WindowCloseEvent& e);
    bool OnWindowResizeEvent(Event& e);

  private:
    std::unique_ptr<Window> m_window;
    LayerStack              m_layer_stack;
    ImguiLayer*             m_imgui_layer;
    Rendering::RenderModule m_rmodule;

    bool m_running;
};

Application* CreateApplication();

} // namespace Firefly