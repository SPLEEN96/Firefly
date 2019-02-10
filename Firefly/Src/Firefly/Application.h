#pragma once
#include "FFLY_CORE.h"
#include "Firefly/FFLYImgui.h"
#include "Firefly/Window.h"

namespace Firefly {

class Application {
  public:
    Application();
    virtual ~Application();

    void Run();
    bool OnEvent(Event& e);

    const bool& IsRunning() const { return m_running; }

  private:
    std::unique_ptr<Window> m_window;
    GUI*                    m_gui;
    bool                    m_running;
};

Application* CreateApplication();

} // namespace Firefly