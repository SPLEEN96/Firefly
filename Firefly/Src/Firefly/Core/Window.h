#pragma once
#include "FFLY_CORE.h"
#include "PCH_CORE.h"

#include "Events/Event.h"

#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

namespace Firefly {

struct WindowData {
    friend struct Window;

    uint8       Handle;
    std::string Title;
    uint32      Width;
    uint32      Height;

    std::function<bool(Event& e)> CallbackFn;

  private:
    union {
        /* LINUX_DATA */
        struct {
            void* Window;
        } linux;

        /* WINDOW_DATA */
        struct {
            void* Window;
        } win32;
    };
};

struct Window {
    static Window* Create(std::string title, uint16 width, uint16 height);
    void           Initialize();
    void           OnUpdate();

    void BindEventCallBackFn(std::function<bool(Event& e)> Callback) {
        Data().CallbackFn = Callback;
    }
    WindowData& Data() { return m_data; }

    void* GetPlatformWindow();

  private:
    uint8      DataHandle;
    WindowData m_data;
};

} // namespace Firefly
