#pragma once
#include "Core/Layer.h"
#include "Core/Window.h"

namespace Firefly {

class ImguiLayer : public Layer {
  public:
    ImguiLayer(Window* window);
    ~ImguiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnImGuiRender() override;
    void OnEvent(Event& event) override;

  private:
    Window* m_window;
};

} // namespace Firefly