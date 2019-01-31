#pragma once
#include "FFLY_CORE.h"
#include "Firefly/Window.h"

#include <GLFW/glfw3.h>

namespace Firefly {

class LinuxWindow : public Window {
  public:
    LinuxWindow(const WinAttributes& attributes = WinAttributes());
    virtual ~LinuxWindow();

    void Initialize() override;
    void InitGLFWCallbacks();
    void OnUpdate() override;

    virtual void SetEventCallbackFn(bool (*CallbackFn)(const Event& e)) {
        m_data.EventCallbackFn = CallbackFn;
    }
    const ui32& GetWidth() const override { return m_data.Width; }
    const ui32& GetHeight() const override { return m_data.Height; }

  private:
    GLFWwindow* m_window;

    struct WinData {
        std::string Title;
        int         Width;
        int         Height;

        bool (*EventCallbackFn)(const Event& e);
    };
    WinData m_data;
};
} // namespace Firefly