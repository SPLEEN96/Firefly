/* TODO
=== ENGINE ===
!!OKEYY!! Shader Class <--(1) !!OKEYY!!
-Camera Class <--(3)
-Transform Class <--(4)

=== OPENGL PRIMITIVES ===
-VAO abstraction <-- (5)

=== RENDERING ARCHITECTURE ===
-Framebuffer
-CommandQueue
-FrameGraph

=== FACTORY ===
!!OKEYY!! Create function for every objects !!OKEYY!!
-Memory management
-Factory class??

=== Assets ===
!!OKEYY!! Texture  <--(2) !!OKEYY!!
-Material
-Mesh
-Model
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