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
    void OnImGuiDraw() override;

    void Begin();
    void End();


  private:
    Window* m_window;
};

} // namespace Firefly